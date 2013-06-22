#ifndef _PARSE_H
#define _PARSE_H

#include "sxhkd.h"

#define RELEASE_PREFIX       '@'
#define MOTION_PREFIX        '!'
#define REPLAY_PREFIX        ':'
#define START_COMMENT        '#'
#define MAGIC_INHIBIT        '\\'
#define PARTIAL_LINE         '\\'
#define LNK_SEP              ";"
#define SYM_SEP              "+ "
#define SEQ_BEGIN            '{'
#define SEQ_END              '}'
#define SEQ_SEP              ","

typedef struct chunk_t chunk_t;
struct chunk_t {
    char text[MAXLEN];
    char item[MAXLEN];
    char *advance;
    bool sequence;
    char range_cur;
    char range_max;
    chunk_t *next;
};

xcb_keysym_t Alt_L, Alt_R, Super_L, Super_R, Hyper_L, Hyper_R,
             Meta_L, Meta_R, Mode_switch, Num_Lock, Scroll_Lock;

void load_config(char *);
void parse_event(xcb_generic_event_t *, uint8_t, xcb_keysym_t *, xcb_button_t *, uint16_t *);
void process_hotkey(char *, char *);
void render_next(chunk_t *, char *);
chunk_t *extract_chunks(char *);
char *get_token(char *, char *, char *);
chunk_t *make_chunk(void);
void destroy_chunks(chunk_t *);
bool parse_chain(char *, chain_t *);
bool parse_keysym(char *, xcb_keysym_t *);
bool parse_button(char *, xcb_button_t *);
bool parse_modifier(char *, uint16_t *);
bool parse_fold(char *, char *);
uint8_t key_to_button(uint8_t);
void get_standard_keysyms(void);
void get_lock_fields(void);
int16_t modfield_from_keysym(xcb_keysym_t);
xcb_keycode_t *keycodes_from_keysym(xcb_keysym_t);

#endif