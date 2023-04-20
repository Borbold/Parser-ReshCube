#include "result_parcer.h"

void free_result(parser_result *par) {
  for (int i = 0; i < par->arg_num; i++) {
    free(par[i].arg_list);
  }
  free(par->arg_list);
  free(par);
}