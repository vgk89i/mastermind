#include <stdint.h>
#include "../config.h"

#ifndef __MM_CORE_H
#define __MM_CORE_H

#define MM_NEW 0
#define MM_PLAYING 1
#define MM_SUCCESS 2
#define MM_FAIL 4

#define MM_CONF_INT 0
#define MM_CONF_STR 1
#define MM_CONF_BOOL 2

typedef struct {
	uint8_t guesses; // max guesses on panel
	uint8_t colors;  // max nbre of colors
	uint8_t holes;   // nbre of holes (items) in a combination
	uint8_t remise;  // do/don't repeat color on combination
} mm_config;
typedef struct {
	uint8_t *combination; // given combination (guess)
	uint8_t inplace;      // nbre of items on right place
	uint8_t insecret;     // nbre of items on secret but not inplace
} mm_guess;
typedef struct {
	uint8_t *val;  // len: config->holes
	uint8_t *freq; // len: config->colors
} mm_secret;
typedef struct {
	uint8_t guessed;   // nbre of user guessed combination
	uint8_t state;     // current state of session
	char *account;     // account name or NULL for default account
	mm_secret *secret; // secret combination to guess
	mm_config *config; // session config
	mm_guess *panel;   // session panel
} mm_session;
typedef struct {
	uint8_t type;
	char *name;
	int val;
	int min;
	int max;
} mm_conf_int_t;
typedef struct {
	uint8_t type;
	char *name;
	char *val;
	uint8_t len;
} mm_conf_str_t;
typedef struct {
	uint8_t type;
	char *name;
	uint8_t val;
} mm_conf_bool_t;
typedef union {
	uint8_t type;
	mm_conf_str_t str;
	mm_conf_bool_t bool;
	mm_conf_int_t nbre;
} mm_conf_t;
typedef struct {
	long unsigned score;
	char *account;
} mm_score_t;
typedef struct {
	mm_score_t *T;
	unsigned max;
	unsigned len;
} mm_scores_t;

extern mm_conf_t mm_confs[7];

mm_session *mm_session_new();
mm_session *mm_session_restore();
unsigned int mm_session_save(mm_session *);
void mm_session_free(mm_session *);
void mm_session_exit(mm_session *);

mm_config *mm_config_load();
void mm_config_save();
unsigned mm_config_set(const char *, const char *);

const mm_scores_t *mm_scores_get();
long unsigned mm_score(mm_session *session);

mm_secret *mm_secret_new(mm_config *);
unsigned mm_play(mm_session *, uint8_t *);
void mm_init();
#endif
