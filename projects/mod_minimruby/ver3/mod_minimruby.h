#ifndef MOD_MINIMRUBY_H
#define MOD_MINIMRUBY_H

void mrb_minim_request_gem_init(mrb_state *mrb);
void minim_push_request(request_rec *r);
void minim_clear_request(void);

#endif
