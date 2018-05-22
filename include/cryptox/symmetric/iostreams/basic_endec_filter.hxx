#pragma once
#include <boost/iostreams/filter/symmetric.hpp>
#include <boost/iostreams/pipeline.hpp>
#include <boost/asio/basic_streambuf.hpp>
#include <memory>
#include <deque>

#include <cryptox/symmetric/symmetric_algorithm.hxx>
#include <cryptox/symmetric/encryptor.hxx>
#include <cryptox/symmetric/decryptor.hxx>

#include <iostream> // XXX

#define BOOST_IOSTREAMS_EVP_FILTER_DEBUG

namespace cryptox {

	template <class Endec>
	class basic_endec_filter : boost::noncopyable {
		typedef typename Endec::algorithm_type algorithm_type;

		// Yes, we must be compatible with C++03... :(
		std::auto_ptr<Endec> _endec;

		// Input partial block
		// This will hold anywhere from 0 to cipher-block_size - 1.
		std::vector<char> _partial;

		// Cached output
		std::deque<char> _output;

		bool _finalized;

		template <class Char>
		int update(const Char* input, const size_t input_size) {
			std::cerr << "+ update(): input_size=" << input_size << std::endl;

			BOOST_ASSERT(16384 > input_size);
			char ciphertext[16384];

			char* last = _endec->update(input, input+input_size, ciphertext);
			const int update_size = std::distance(ciphertext, last);
			std::cerr << "\tupdate_size=" << update_size << std::endl;
			if (update_size < 0)
				return update_size;

			// Write though debug line...
			//std::copy_n(input, input_size, std::back_inserter(_output));
			
			std::copy_n(ciphertext, update_size, std::back_inserter(_output));
			return update_size;
		}
		
		int finalize() {
			#ifdef BOOST_IOSTREAMS_EVP_FILTER_DEBUG
			std::cerr << "+ finalize()" << std::endl;
			#endif

			// More than enough for most blocks... (2015)
			char ciphertext[128];

			char* last = _endec->finalize(ciphertext);
			const int size = std::distance(ciphertext, last);
			std::cerr << "\tsize=" << size << std::endl;
			if (size < 0)
				return size;

			std::copy_n(ciphertext, size, std::back_inserter(_output));
			return size;
		}

		template <typename Output>
		void flush2(Output& first, const size_t output_size) {
			#ifdef BOOST_IOSTREAMS_EVP_FILTER_DEBUG
			std::cerr << "+ flush2(): output_size=" << output_size << std::endl;
			#endif

			// Process the rest of the partial...
			if (!_partial.empty()) {
				std::cerr << "\twritting partial bytes. Size=" << _partial.size() << std::endl;
				update(_partial.data(), _partial.size());
				_partial.clear();
			}
			
			if (!_finalized) {
				finalize();
				_finalized = true;
			}

			std::cerr << "+ output_some_data # output_size=" << output_size << std::endl;
			const size_t output_capacity = std::min BOOST_PREVENT_MACRO_SUBSTITUTION(
				output_size,
				_output.size()
			);

			if (!_output.empty()) {
				std::copy_n(_output.begin(), output_capacity, first);
				std::cerr << "\twrote=" << output_capacity << std::endl;
				_output.erase(_output.begin(), _output.begin() + output_capacity);
				first += output_capacity;
				
				#ifdef BOOST_IOSTREAMS_EVP_FILTER_DEBUG
				static size_t total_output_capacity;
				total_output_capacity += output_capacity;
				std::cerr <<  "\tW="  << output_capacity << ' ' << "TW=" << total_output_capacity << ' ' << std::endl;
				#endif
			}
		}

	public:
		typedef char char_type;

		basic_endec_filter(Endec* endec)
		 : _endec(endec), _finalized(false) {
		}

		bool filter(const char*& src_begin, const char* src_end, char*& dest_begin, char* dest_end, bool must_flush) {
			const size_t  input_size = std::distance( src_begin,  src_end);
			const size_t output_size = std::distance(dest_begin, dest_end);

			const size_t chunk = std::min BOOST_PREVENT_MACRO_SUBSTITUTION(input_size, output_size);

			std::cerr << "+ filter()"
			          << " must_flush=" <<   must_flush
			          << "  F[i,o]=("   <<  input_size
			          <<         " ,"   << output_size << ")"
			          << " chunk=" << chunk
			          << std::endl;

			auto tmp = dest_begin;
			dest_begin = _endec->update(src_begin, src_begin + chunk, dest_begin);

			const size_t written = std::distance(tmp, dest_begin);
			std::cerr << "\twritten=" << written << std::endl;

			src_begin += chunk;

			if (must_flush)
				dest_begin = _endec->finalize(dest_begin);

			const bool done = (input_size == 0 && !must_flush);
			std::cerr << "AFTER+ filter()"
			          << " must_flush=" <<   must_flush
			          << "  F[i,o]=("   <<  std::distance(src_begin, src_end)
			          <<         " ,"   <<  std::distance(dest_begin, dest_end) << ")"
			          << " chunk=" << chunk
			          << " ret=" << !done
			          << std::endl;

			return !done;
		}

		bool filter22(const char*& src_begin, const char* src_end, char*& dest_begin, char* dest_end, bool must_flush) {
			const size_t block_size = algorithm_type::block_size();

			size_t  input_size = std::distance( src_begin,  src_end);
			size_t output_size = std::distance(dest_begin, dest_end);

#ifdef BOOST_IOSTREAMS_EVP_FILTER_DEBUG
			static size_t  total_input_size = 0;
			static size_t total_output_size = 0;
			
			total_input_size +=  input_size;
			total_output_size += output_size;
			
			std::cout << "+ filter()"
			          << " must_flush=" << must_flush
			          << "  F[i,o]=(" <<       input_size << ',' <<       output_size << ")"
			          << " TF[i,o]=(" << total_input_size << ',' << total_output_size << ")"
			          << std::endl;
#endif

			//
			// Full blocks available for processing.
			// Partial block residue will be processed on flush.
			//
			const size_t partial_block_bytes = (input_size % block_size);
			const size_t complete_block_bytes = input_size - partial_block_bytes;

			BOOST_ASSERT( partial_block_bytes < block_size);
			BOOST_ASSERT(complete_block_bytes % block_size == 0);

			std::cerr << "\t partial_block_bytes=" <<  partial_block_bytes << std::endl;
			std::cerr << "\tcomplete_block_bytes=" << complete_block_bytes << std::endl;

			// Write complete blocks...
			if (complete_block_bytes > 0) {
				update(src_begin, complete_block_bytes);
				src_begin += complete_block_bytes;
			}

			// Now buffer the remaining partial block bytes.
			if (partial_block_bytes != 0) {
				// Just to make sure this is really a partial.
				BOOST_ASSERT(src_begin + partial_block_bytes == src_end);

				std::copy_n(src_begin, partial_block_bytes, std::back_inserter(_partial));
				src_begin += partial_block_bytes;
			}

			if (must_flush)
				flush2(dest_begin, output_size);

			return input_size != 0;
		}

		void close() {
			std::cerr << "+ basic_endec_filter::close()" << std::endl;
			_endec->reset();
		}
	};

}

namespace cryptox {

	template <class Endec>
	struct basic_evp_filter : boost::iostreams::symmetric_filter<
		basic_endec_filter<Endec>
	> {
	private:
		typedef basic_endec_filter<Endec> impl_type;
		typedef boost::iostreams::symmetric_filter<impl_type> base_type;
	public:
		typedef typename base_type::char_type char_type;
		typedef typename base_type::category  category;

		basic_evp_filter(Endec* endec, int buffer_size = boost::iostreams::default_device_buffer_size)
		 : base_type(buffer_size, endec) {
			std::cerr << "* basic_evp_filter<>: block_size=" << Endec::algorithm_type::block_size() << std::endl;
		}
	};

	BOOST_IOSTREAMS_PIPABLE(basic_evp_filter, 1)

}

namespace cryptox {

	template <class T>
	basic_evp_filter<T> create_filter(T* x) {
		return basic_evp_filter<T>(x);
	}

}
