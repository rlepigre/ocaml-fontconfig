#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/callback.h>
#include <caml/fail.h>
#include <fontconfig/fontconfig.h>

#include "fccaml.h"

/* Matrix */

CAMLprim FcMatrix *fcmatrix_from_caml(value m)
{
  CAMLparam0();
  FcMatrix *res = malloc(sizeof(*res));
  res->xx = Double_field(m, 0);
  res->xy = Double_field(m, 1);
  res->yx = Double_field(m, 2);
  res->yy = Double_field(m, 3);
  return res;
}

CAMLprim value caml_from_fcmatrix(const FcMatrix *m)
{
  CAMLparam0();
  CAMLlocal2(res, arr);
  res = caml_alloc(1, 4);
  arr = caml_alloc(4 * Double_wosize, Double_array_tag);
  Store_field(res, 1, arr);
  Store_double_field(arr, 0, m->xx);
  Store_double_field(arr, 1, m->xy);
  Store_double_field(arr, 2, m->yx);
  Store_double_field(arr, 3, m->yy);
  CAMLreturn(res);
}

CAMLprim value matrix_multiply(value m1, value m2)
{
  CAMLparam0();
  CAMLlocal1(res);
  FcMatrix *mm1, *mm2, *mres;

  mm1 = fcmatrix_from_caml(m1);
  mm2 = fcmatrix_from_caml(m2);
  mres = malloc(sizeof(*mres));
  FcMatrixMultiply(mres, mm1, mm2);

  res = caml_from_fcmatrix(mres);
  free(mres);
  free(mm1);
  free(mm2);
  
  CAMLreturn(res);
}

CAMLprim value matrix_rotate(value m, value cos, value sin)
{
  CAMLparam0();
  CAMLlocal1(res);
  FcMatrix *mm;

  mm = fcmatrix_from_caml(m);
  FcMatrixRotate(mm, Double_val(cos), Double_val(sin));

  res = caml_from_fcmatrix(mm);
  free(mm);

  CAMLreturn(res);
}

CAMLprim value matrix_scale(value m, value sx, value sy)
{
  CAMLparam0();
  CAMLlocal1(res);
  FcMatrix *mm;

  mm = fcmatrix_from_caml(m);
  FcMatrixScale(mm, Double_val(sx), Double_val(sy));

  res = caml_from_fcmatrix(mm);
  free(mm);

  CAMLreturn(res);
}

CAMLprim value matrix_shear(value m, value sh, value sv)
{
  CAMLparam0();
  CAMLlocal1(res);
  FcMatrix *mm;

  mm = fcmatrix_from_caml(m);
  FcMatrixShear(mm, Double_val(sh), Double_val(sv));

  res = caml_from_fcmatrix(mm);
  free(mm);

  CAMLreturn(res);
}
