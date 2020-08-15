#include <stdio.h>
#include <mruby.h>
#include <mruby/error.h>
#include <mruby/throw.h>

void handle_error(mrb_state *mrb) {
  struct mrb_jmpbuf c_jump;
  mrb->jmp = &c_jump;
  MRB_TRY(mrb->jmp) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Test error!");
  }
  MRB_CATCH(mrb->jmp) {
    if(mrb->exc) {
      printf("Error is successfully catched: ");
      mrb_p(mrb, mrb_obj_value(mrb->exc));
    } else {
      printf("Catched but exc is null\n");
    }
  }
  MRB_END_EXC(mrb->jmp) {}
  mrb->jmp = NULL;
}

int main(int argc, char *argv[]) {
  mrb_state *mrb = mrb_open();
  handle_error(mrb);
  return 0;
}
