// [===========================================================================]
// [                               C r y p t o x                               ]
// [---------------------------------------------------------------------------]
// [                                                                           ]
// [                          Copyright (C) 2016-2018                          ]
// [                      Rodrigo Madera <madera@acm.org>                      ]
// [                                                                           ]
// [---------------------------------------------------------------------------]
// [         Distributed under the Boost Software License, Version 1.0         ]
// [ Read accompanying LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt ]
// [===========================================================================]

#pragma once

#define CRYPTOX_SYMMETRIC_ALGORITHM_NULL \
	((enc_null, "UNDEF"))

#ifdef OPENSSL_NO_DES
#  define CRYPTOX_SYMMETRIC_ALGORITHM_DES
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_DES   \
	((des_cbc,        "DES-CBC"      )) \
	((des_cfb,        "DES-CFB"      )) \
	((des_cfb1,       "DES-CFB1"     )) \
	((des_cfb8,       "DES-CFB8"     )) \
	((des_cfb64,      "DES-CFB"      )) \
	((des_ecb,        "DES-ECB"      )) \
	((des_ofb,        "DES-OFB"      )) \
	((des_ede,        "DES-EDE"      )) \
	((des_ede_cbc,    "DES-EDE-CBC"  )) \
	((des_ede_ecb,    "DES-EDE"      )) \
	((des_ede_cfb,    "DES-EDE-CFB"  )) \
	((des_ede_ofb,    "DES-EDE-OFB"  )) \
	((des_ede3,       "DES-EDE3"     )) \
	((des_ede3_cbc,   "DES-EDE3-CBC" )) \
	((des_ede3_ecb,   "DES-EDE3"     )) \
	((des_ede3_cfb,   "DES-EDE3-CFB" )) \
	((des_ede3_cfb1,  "DES-EDE3-CFB1")) \
	((des_ede3_cfb8,  "DES-EDE3-CFB8")) \
	((des_ede3_cfb64, "DES-EDE3-CFB" )) \
	((des_ede3_ofb,   "DES-EDE3-OFB" )) \
	/* ((des_ede3_wrap,  "id-smime-alg-CMS3DESwrap")) [Crashing] */ \
	((desx_cbc,       "DESX-CBC"     ))
#endif

#ifdef OPENSSL_NO_RC2
#  define CRYPTOX_SYMMETRIC_ALGORITHM_RC2
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_RC2 \
	((rc2_ecb,    "RC2-ECB"   ))      \
	((rc2_cbc,    "RC2-CBC"   ))      \
	((rc2_40_cbc, "RC2-40-CBC"))      \
	((rc2_64_cbc, "RC2-64-CBC"))      \
	((rc2_cfb,    "RC2-CFB"   ))      \
	((rc2_cfb64,  "RC2-CFB"   ))      \
	((rc2_ofb,    "RC2-OFB"   ))
#endif

#ifdef OPENSSL_NO_RC4
#  define CRYPTOX_SYMMETRIC_ALGORITHM_RC4
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_RC4 \
	((rc4,          "RC4"         ))  \
	((rc4_40,       "RC4-40"      ))  \
	((rc4_hmac_md5, "RC4-HMAC-MD5"))
#endif

#ifdef OPENSSL_NO_RC5
#  define CRYPTOX_SYMMETRIC_ALGORITHM_RC5
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_RC5 \
	((rc5_32_12_16_cbc,   "TODO"))    \
	((rc5_32_12_16_ecb,   "TODO"))    \
	((rc5_32_12_16_cfb,   "TODO"))    \
	((rc5_32_12_16_cfb64, "TODO"))    \
	((rc5_32_12_16_ofb,   "TODO"))
#endif

#ifdef OPENSSL_NO_IDEA
#  define CRYPTOX_SYMMETRIC_ALGORITHM_IDEA
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_IDEA \
	((idea_ecb,   "IDEA-ECB"))         \
	((idea_cfb,   "IDEA-CFB"))         \
	((idea_cfb64, "IDEA-CFB"))         \
	((idea_ofb,   "IDEA-OFB"))         \
	((idea_cbc,   "IDEA-CBC"))
#endif

#ifdef OPENSSL_NO_BF
#  define CRYPTOX_SYMMETRIC_ALGORITHM_BF
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_BF \
	((bf_ecb,   "BF-ECB"))           \
	((bf_cbc,   "BF-CBC"))           \
	((bf_cfb,   "BF-CFB"))           \
	((bf_cfb64, "BF-CFB"))           \
	((bf_ofb,   "BF-OFB"))
#endif

#ifdef OPENSSL_NO_CAST
#  define CRYPTOX_SYMMETRIC_ALGORITHM_CAST
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_CAST \
	((cast5_ecb,   "CAST5-ECB"))       \
	((cast5_cbc,   "CAST5-CBC"))       \
	((cast5_cfb,   "CAST5-CFB"))       \
	((cast5_cfb64, "CAST5-CFB"))       \
	((cast5_ofb,   "CAST5-OFB"))
#endif

#ifdef OPENSSL_NO_AES
#  define CRYPTOX_SYMMETRIC_ALGORITHM_AES
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_AES  \
	((aes_128_ecb,    "AES-128-ECB" )) \
	((aes_128_cbc,    "AES-128-CBC" )) \
	((aes_128_cfb,    "AES-128-CFB" )) \
	((aes_128_cfb1,   "AES-128-CFB1")) \
	((aes_128_cfb8,   "AES-128-CFB8")) \
	((aes_128_cfb128, "AES-128-CFB" )) \
	((aes_128_ofb,    "AES-128-OFB" )) \
	((aes_128_ctr,    "AES-128-CTR" )) \
	/*((aes_128_ccm,  "id-aes128-CCM" ))*/ \
	/*((aes_128_gcm,  "id-aes128-GCM" ))*/ \
	/*((aes_128_xts,  "AES-128-XTS"   ))*/ \
	/*((aes_128_wrap, "id-aes128-wrap"))*/ \
	\
	((aes_192_ecb,    "AES-192-ECB"))   \
	((aes_192_cbc,    "AES-192-CBC"))   \
	((aes_192_cfb,    "AES-192-CFB"))   \
	((aes_192_cfb1,   "AES-192-CFB1"))  \
	((aes_192_cfb8,   "AES-192-CFB8"))  \
	((aes_192_cfb128, "AES-192-CFB"))   \
	((aes_192_ofb,    "AES-192-OFB"))   \
	((aes_192_ctr,    "AES-192-CTR"))   \
	/*((aes_192_ccm,  "id-aes192-CCM" ))*/ \
	/*((aes_192_gcm,  "id-aes192-GCM" ))*/ \
	/*((aes_192_wrap, "id-aes192-wrap"))*/ \
	\
	((aes_256_ecb,    "AES-256-ECB"))   \
	((aes_256_cbc,    "AES-256-CBC"))   \
	((aes_256_cfb,    "AES-256-CFB"))   \
	((aes_256_cfb1,   "AES-256-CFB1"))  \
	((aes_256_cfb8,   "AES-256-CFB8"))  \
	((aes_256_cfb128, "AES-256-CFB"))   \
	((aes_256_ofb,    "AES-256-OFB"))   \
	((aes_256_ctr,    "AES-256-CTR"))   \
	/*((aes_256_ccm,  "id-aes256-CCM" ))*/ \
	/*((aes_256_gcm,  "id-aes256-GCM" ))*/ \
	/*((aes_256_wrap, "id-aes256-wrap"))*/ \
	/*((aes_256_xts,    "AES-256-XTS"))*/
#endif

#ifdef OPENSSL_NO_CAMELLIA
#  define CRYPTOX_SYMMETRIC_ALGORITHM_CAMELLIA
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_CAMELLIA       \
	((camellia_128_ecb,    "CAMELLIA-128-ECB" )) \
	((camellia_128_cbc,    "CAMELLIA-128-CBC" )) \
	((camellia_128_cfb,    "CAMELLIA-128-CFB" )) \
	((camellia_128_cfb1,   "CAMELLIA-128-CFB1")) \
	((camellia_128_cfb8,   "CAMELLIA-128-CFB8")) \
	((camellia_128_cfb128, "CAMELLIA-128-CFB" )) \
	((camellia_128_ofb,    "CAMELLIA-128-OFB" )) \
	\
	((camellia_192_ecb,    "CAMELLIA-192-ECB" )) \
	((camellia_192_cbc,    "CAMELLIA-192-CBC" )) \
	((camellia_192_cfb,    "CAMELLIA-192-CFB" )) \
	((camellia_192_cfb1,   "CAMELLIA-192-CFB1")) \
	((camellia_192_cfb8,   "CAMELLIA-192-CFB8")) \
	((camellia_192_cfb128, "CAMELLIA-192-CFB" )) \
	((camellia_192_ofb,    "CAMELLIA-192-OFB" )) \
	\
	((camellia_256_ecb,    "CAMELLIA-256-ECB" )) \
	((camellia_256_cbc,    "CAMELLIA-256-CBC" )) \
	((camellia_256_cfb,    "CAMELLIA-256-CFB" )) \
	((camellia_256_cfb1,   "CAMELLIA-256-CFB1")) \
	((camellia_256_cfb8,   "CAMELLIA-256-CFB8")) \
	((camellia_256_cfb128, "CAMELLIA-256-CFB" )) \
	((camellia_256_ofb,    "CAMELLIA-256-OFB" ))
#endif

#ifdef OPENSSL_NO_SEED
#  define CRYPTOX_SYMMETRIC_ALGORITHM_SEED
#else
#  define CRYPTOX_SYMMETRIC_ALGORITHM_SEED \
	((seed_ecb,    "SEED-ECB" ))       \
	((seed_cbc,    "SEED-CBC" ))       \
	((seed_cfb,    "SEED-CFB" ))       \
	((seed_cfb128, "SEED-CFB" ))       \
	((seed_ofb,    "SEED-OFB" ))
#endif

#define CRYPTOX_SYMMETRIC_ALGORITHMS         \
	CRYPTOX_SYMMETRIC_ALGORITHM_NULL     \
	CRYPTOX_SYMMETRIC_ALGORITHM_DES      \
	CRYPTOX_SYMMETRIC_ALGORITHM_RC2      \
	CRYPTOX_SYMMETRIC_ALGORITHM_RC4      \
	CRYPTOX_SYMMETRIC_ALGORITHM_RC5      \
	CRYPTOX_SYMMETRIC_ALGORITHM_IDEA     \
	CRYPTOX_SYMMETRIC_ALGORITHM_BF       \
	CRYPTOX_SYMMETRIC_ALGORITHM_CAST     \
	CRYPTOX_SYMMETRIC_ALGORITHM_AES      \
	CRYPTOX_SYMMETRIC_ALGORITHM_CAMELLIA \
	CRYPTOX_SYMMETRIC_ALGORITHM_SEED
