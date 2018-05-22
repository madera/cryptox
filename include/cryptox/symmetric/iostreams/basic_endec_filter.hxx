#pragma once
#include <boost/iostreams/filter/symmetric.hpp>
#include <memory>
#include <deque>

namespace cryptox {

	template <class Endec>
	class basic_endec_filter : boost::noncopyable {
		typedef typename Endec::algorithm_type algorithm_type;

		// Yes, we must be compatible with C++03... :(
		std::auto_ptr<Endec> _endec;

		// Cached output
		std::deque<char> _output;
		bool _finalized;
		
		void finalize() {
			if (!_finalized) {
				_endec->finalize(std::back_inserter(_output));
				_finalized = true;
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

			// Process Input...
			_endec->update(src_begin, src_end, std::back_inserter(_output));
			src_begin = src_end;

			// Process Output...
			const size_t output_capacity = std::min BOOST_PREVENT_MACRO_SUBSTITUTION(
				output_size,
				_output.size()
			);

			if (!_output.empty()) {
				std::copy_n(_output.begin(), output_capacity, dest_begin);
				_output.erase(_output.begin(), _output.begin() + output_capacity);
				dest_begin += output_capacity;
			}

			if (must_flush) {
				finalize();
				return !_output.empty();
			}

			return input_size != 0;
		}

		void close() {
			_endec->reset();
			_finalized = false;
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
