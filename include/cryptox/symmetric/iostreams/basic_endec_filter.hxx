#pragma once
#include <boost/iostreams/filter/symmetric.hpp>
#include <memory>
#include <deque>

namespace cryptox {

	template <class Endec>
	class basic_endec_filter : boost::noncopyable {
		typedef typename Endec::algorithm_type algorithm_type;

protected:
		// Yes, we must be compatible with C++03... :(
		std::auto_ptr<Endec> _endec;

		// Cached output.
		std::deque<char> _output;
		bool _finalized;
		
		std::size_t _total_input;
		std::size_t _total_output;

		void finalize() {
			if (!_finalized)
				if (_endec->total_input() > 0) // XXX: Discard unused rotation.
					_endec->finalize(std::back_inserter(_output));

			_finalized = true;
		}

	protected:
		void reset_endec(Endec* newcomer) {
			_endec.reset(newcomer);
			_finalized = false;
		}

	public:
		typedef char char_type;

		basic_endec_filter(Endec* endec)
		 : _endec(endec),
		   _finalized(false),
		   _total_input(0),
		   _total_output(0) {
		}

		bool filter(const char*& src_begin, const char* src_end, char*& dest_begin, char* dest_end, bool must_flush) {
			const size_t  input_size = std::distance( src_begin,  src_end);
			const size_t output_size = std::distance(dest_begin, dest_end);

			// Process Input...
			_endec->update(src_begin, src_end, std::back_inserter(_output));
			_total_input += std::distance(src_begin, src_end);
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
				_total_output += output_capacity;
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

		const size_t total_input() const {
			return _total_input;
		}

		const size_t total_output() const {
			return _total_output;
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
