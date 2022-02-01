#pragma once
#include "basic_endec_filter.hxx"
#include "../../detail/is_encryptor.hxx"
#include "../../detail/is_decryptor.hxx"
#include <boost/iostreams/filter/symmetric.hpp>
#include <memory>
#include <deque>

namespace cryptox {

	template <class Endec, class KeyProvider>
	class rotating_endec_filter : public basic_endec_filter<Endec> {
		typedef basic_endec_filter<Endec> base_type;

		KeyProvider _key_provider;
		size_t _period;

	public:
		rotating_endec_filter(const KeyProvider& key_provider, const size_t period = 0)
		 : base_type(0),
		  _key_provider(key_provider),
		  _period(std::max(period, Endec::algorithm_type::block_size())) {
			this->rotate();
		}

		void rotate() {
			if (this->_endec.get())
				this->finalize();

			const auto& newcomer = _key_provider();
			this->reset_endec(
				new Endec(
					newcomer.key.begin(), newcomer.key.end(),
					newcomer. iv.begin(), newcomer. iv.end()
				)
			);
		}

		bool filter(const char*& src_begin, const char* src_end, char*& dest_begin, char* dest_end, bool must_flush) {
			size_t  input_size = std::distance( src_begin,  src_end);
			size_t output_size = std::distance(dest_begin, dest_end);

			// TODO: Separate this class into encryptor and decryptor filters.
			//       For now, just if-it.
			if (_period != 0 && detail::is_encryptor<Endec>::value) {
				size_t  input_size = std::distance( src_begin,  src_end);
				size_t output_size = std::distance(dest_begin, dest_end);

				const size_t b0 =  this->total_input()               / _period;
				const size_t b1 = (this->total_input() + input_size) / _period;

				// Block change?
				if (b0 != b1) {
					int loop = 0;

					size_t left = _period - (this->total_input() % _period);
					size_t available_input = std::min BOOST_PREVENT_MACRO_SUBSTITUTION(input_size, left);

					bool done = false;
					while (!done && left > 0 && available_input > 0) {
						done = !base_type::filter(src_begin, src_begin + available_input, dest_begin, dest_end, false);
						left -= available_input;

						 input_size = std::distance( src_begin,  src_end);
						output_size = std::distance(dest_begin, dest_end);
						available_input = std::min BOOST_PREVENT_MACRO_SUBSTITUTION(input_size, left);
					}

					rotate();

					return true;
				}
			}

			// TODO: Separate this class into encryptor and decryptor filters.
			//       For now, just if-it.
			if (_period != 0 && detail::is_decryptor<Endec>::value) {
				bool done = false;
				while (!done && input_size > Endec::algorithm_type::block_size()) {
					// FIXME: Only consuming one block at a time.

					done = !base_type::filter(src_begin, src_begin + Endec::algorithm_type::block_size(), dest_begin, dest_end, false);
					input_size = std::distance(src_begin, src_end);

					if (this->_endec->total_output() == _period)
						rotate();
				}

				if (must_flush)
					rotate();
			}

			 input_size = std::distance( src_begin,  src_end);
			output_size = std::distance(dest_begin, dest_end);

			return base_type::filter(src_begin, src_end, dest_begin, dest_end, must_flush);
		}
	};

}

namespace cryptox {

	template <class Endec, class KeyProvider>
	struct rotating_evp_filter : boost::iostreams::symmetric_filter<
		rotating_endec_filter<Endec, KeyProvider>
	> {
	private:
		typedef rotating_endec_filter<Endec, KeyProvider> impl_type;
		typedef boost::iostreams::symmetric_filter<impl_type> base_type;
	public:
		typedef typename base_type::char_type char_type;
		typedef typename base_type::category  category;

		rotating_evp_filter(const KeyProvider& key_provider, const size_t period = 0,
		                    int buffer_size = boost::iostreams::default_device_buffer_size)
		 : base_type(buffer_size, key_provider, period) {
		}
	};

	BOOST_IOSTREAMS_PIPABLE(rotating_evp_filter, 2)
}

namespace cryptox {

	template <class Endec, class KeyProvider>
	rotating_evp_filter<Endec, KeyProvider>
	create_rotating_filter(const KeyProvider& key_provider, const size_t period = 0) {
		return rotating_evp_filter<Endec, KeyProvider>(key_provider, period);
	}

}
