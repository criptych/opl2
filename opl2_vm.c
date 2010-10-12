#include "opl2.h"
#include "opl2_int.h"

#include <math.h>

/******************************************************************************/

void pl2MultMatrix4f(fmatrix4_t *out, const fmatrix4_t *a, const fmatrix4_t *b)
{
#if _PSP_FW_VERSION
    asm volatile (
        "ulv.q   c100,  0+%1\n"
        "ulv.q   c110, 16+%1\n"
        "ulv.q   c120, 32+%1\n"
        "ulv.q   c130, 48+%1\n"
        "ulv.q   c200,  0+%2\n"
        "ulv.q   c210, 16+%2\n"
        "ulv.q   c220, 32+%2\n"
        "ulv.q   c230, 48+%2\n"
        "vmmul.q m000, m100, m200\n"
        "usv.q   c000,  0+%0\n"
        "usv.q   c010,  0+%0\n"
        "usv.q   c020,  0+%0\n"
        "usv.q   c030,  0+%0\n"
        :"=m"(*out)
        :"m"(*a), "m"(*b)
    );
#else
    fmatrix4_t c;
# define MMUL(i,j) \
    c.i.j = a->x.j * b->i.x + a->y.j * b->i.y + a->z.j * b->i.z + a->w.j*b->i.w
    MMUL(x,x); MMUL(y,x); MMUL(z,x); MMUL(w,x);
    MMUL(x,y); MMUL(y,y); MMUL(z,y); MMUL(w,y);
    MMUL(x,z); MMUL(y,z); MMUL(z,z); MMUL(w,z);
    MMUL(x,w); MMUL(y,w); MMUL(z,w); MMUL(w,w);
# undef MMUL
    *out = c;
#endif // _PSP_FW_VERSION
}

void pl2VectorTransform4f(fvector4_t *out, const fmatrix4_t *m, const fvector4_t *v)
{
#if _PSP_FW_VERSION
    asm volatile (
        "ulv.q   c100,  0+%1\n"
        "ulv.q   c110, 16+%1\n"
        "ulv.q   c120, 32+%1\n"
        "ulv.q   c130, 48+%1\n"
        "ulv.q   c010,  0+%2\n"
        "vtfm4.q c000, m100, c010\n"
        "usv.q   c000,  0+%0\n"
        :"=m"(*out)
        :"m"(*m), "m"(*v)
    );
#else
    fvector4_t u;
# define VTFM(i) \
    u.i = m->x.i * v->x + m->y.i * v->y + m->z.i * v->z + m->w.i*v->w
    VTFM(x); VTFM(y); VTFM(z); VTFM(w);
# undef VTFM
    *out = u;
#endif // _PSP_FW_VERSION
}

void pl2TransposeMatrix4f(fmatrix4_t *out, const fmatrix4_t *m)
{
#if _PSP_FW_VERSION
    asm volatile(
        "ulv.q  c000,  0+%1\n"
        "ulv.q  c010, 16+%1\n"
        "ulv.q  c020, 32+%1\n"
        "ulv.q  c030, 48+%1\n"
        "usv.q  r000,  0+%0\n"
        "usv.q  r001, 16+%0\n"
        "usv.q  r002, 32+%0\n"
        "usv.q  r003, 48+%0\n"
        :"=m"(*out) :"m"(*m)
    );
#else
# define MTRAN(i,j) \
    n.i.j = m->j.i

    fmatrix4_t n;
    MTRAN(x,x); MTRAN(y,x); MTRAN(z,x); MTRAN(w,x);
    MTRAN(x,y); MTRAN(y,y); MTRAN(z,y); MTRAN(w,y);
    MTRAN(x,z); MTRAN(y,z); MTRAN(z,z); MTRAN(w,z);
    MTRAN(x,w); MTRAN(y,w); MTRAN(z,w); MTRAN(w,w);
    *out = n;

# undef MTRAN
#endif
}

void pl2VectorAdd4f(fvector4_t *out, const fvector4_t *a, const fvector4_t *b)
{
#if _PSP_FW_VERSION
    asm volatile(
        "ulv.q  c010, 0+%1\n"
        "ulv.q  c020, 0+%2\n"
        "vadd.q c000, c010, c020\n"
        "usv.q  c000, 0+%0\n"
        :"=m"(*out)
        :"m"(*a), "m"(*b)
    );
#else
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
    out->w = a->w + b->w;
#endif
}

void pl2VectorSub4f(fvector4_t *out, const fvector4_t *a, const fvector4_t *b)
{
#if _PSP_FW_VERSION
    asm volatile(
        "ulv.q  c010, 0+%1\n"
        "ulv.q  c020, 0+%2\n"
        "vsub.q c000, c010, c020\n"
        "usv.q  c000, 0+%0\n"
        :"=m"(*out)
        :"m"(*a), "m"(*b)
    );
#else
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
    out->w = a->w - b->w;
#endif
}

float pl2VectorDot4f(const fvector4_t *a, const fvector4_t *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

void pl2VectorScale4f(fvector4_t *out, const fvector4_t *v, float s)
{
#if _PSP_FW_VERSION
    asm volatile(
        "mtv    %2, s020\n"
        "ulv.q  c010, 0+%1\n"
        "vscl.q c000, c010, s020\n"
        "usv.q  c000, 0+%0\n"
        :"=m"(*out)
        :"m"(*v), "r"(s)
    );
#else
    out->x = v->x * s;
    out->y = v->y * s;
    out->z = v->z * s;
    out->w = v->w * s;
#endif
}

void pl2VectorScaleAdd4f(fvector4_t *out, const fvector4_t *v, float s)
{
#if _PSP_FW_VERSION
    asm volatile(
        "mtv    %2, s020\n"
        "ulv.q  c000, 0+%0\n"
        "ulv.q  c010, 0+%1\n"
        "vscl.q c010, c010, s020\n"
        "vadd.q c000, c000, c010\n"
        "usv.q  c000, 0+%0\n"
        :"+m"(*out)
        :"m"(*v), "r"(s)
    );
#else
    out->x += v->x * s;
    out->y += v->y * s;
    out->z += v->z * s;
    out->w += v->w * s;
#endif
}

void pl2VectorAdd3f(fvector3_t *out, const fvector3_t *a, const fvector3_t *b)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

void pl2VectorSub3f(fvector3_t *out, const fvector3_t *a, const fvector3_t *b)
{
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}

float pl2VectorDot3f(const fvector3_t *a, const fvector3_t *b)
{
   return a->x * b->x + a->y * b->y + a->z * b->z;
}

void pl2VectorCross3f(fvector3_t *out, const fvector3_t *a, const fvector3_t *b)
{
   fvector3_t c;
   c.x = a->y * b->z - a->z * b->y;
   c.y = a->z * b->x - a->x * b->z;
   c.z = a->x * b->y - a->y * b->x;
   *out = c;
}

void pl2VectorScale3f(fvector3_t *out, const fvector3_t *v, float s)
{
   out->x = v->x * s;
   out->y = v->y * s;
   out->z = v->z * s;
}

void pl2VectorScaleAdd3f(fvector3_t *out, const fvector3_t *v, float s)
{
#if _PSP_FW_VERSION
    asm volatile (
        "mtv    %2, s020\n"
        "ulv.q  c010, 0+%1\n"
        "vscl.t c000, c010, s020\n"
        "sv.s   s000, 0+%0\n"
        "sv.s   s001, 4+%0\n"
        "sv.s   s002, 8+%0\n"
        :"=m"(*out)
        :"m"(*v), "r"(s)
    );
#else
    if(s != s) DEBUGPRINT("%s: s is NaN!\n", __func__);
    out->x += v->x * s;
    out->y += v->y * s;
    out->z += v->z * s;
#endif // _PSP_FW_VERSION
}

float pl2VectorLength3f(const fvector3_t *v)
{
   return sqrtf(pl2VectorDot3f(v, v));
}

void pl2VectorNormalize3f(fvector3_t *out, const fvector3_t *v)
{
   float len = pl2VectorLength3f(v);
   if(len) len = 1.0f / len;
   pl2VectorScale3f(out, v, len);
}

void pl2QuatMultiply(fvector4_t *out, const fvector4_t *a, const fvector4_t *b)
{
   fvector4_t c;
   c.x = a->w * b->x + a->x * b->w + a->y * b->z - a->z * b->y;
   c.y = a->w * b->y + a->y * b->w + a->z * b->x - a->x * b->z;
   c.z = a->w * b->z + a->z * b->w + a->x * b->y - a->y * b->x;
   c.w = a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z;
   *out = c;
}

void pl2QuatRotate(fvector3_t *out, const fvector3_t *v, const fvector3_t *axis, float angle)
{
   float s = sinf(0.5f * angle) / pl2VectorLength3f(axis);
   float c = cosf(0.5f * angle);

   fvector4_t q = { s * axis->x, s * axis->y, s * axis->z, c };
   fvector4_t t = { v->x, v->y, v->z, 0.0f };
   fvector4_t r;

   pl2QuatMultiply(&r, &q, &t);
   q.x = -q.x; q.y = -q.y; q.z = -q.z;
   pl2QuatMultiply(&t, &r, &q);

   out->x = t.x; out->y = t.y; out->z = t.z;
}

void pl2VectorOrbit(fvector3_t *planet, const fvector3_t *sun, const fvector3_t *up, const fvector3_t *rotate)
{
   //DEBUGPRINT("glmOrbit(<%6.3f %6.3f %6.3f>, <%6.3f %6.3f %6.3f>, <%6.3f %6.3f %6.3f>, <%6.3f %6.3f %6.3f>)",
   //   planet->x, planet->y, planet->z, sun->x, sun->y, sun->z, up->x, up->y, up->z, rotate->x, rotate->y, rotate->z);
   fvector3_t fwd, right;
   pl2VectorSub3f(&fwd, planet, sun);
   pl2VectorCross3f(&right, up, &fwd);

   fvector3_t r = fwd;
   pl2QuatRotate(&r, &r, &right, rotate->x);
   pl2QuatRotate(&r, &r, up,     rotate->y);
   pl2QuatRotate(&r, &r, &fwd,   rotate->z);
   pl2VectorAdd3f(planet, &r, sun);

   //DEBUGPRINT(" == <%6.3f %6.3f %6.3f>\n", planet->x, planet->y, planet->z);
}

void pl2VectorZoom(fvector3_t *obj, const fvector3_t *targ, float distance)
{
   fvector3_t t, v;
   pl2VectorSub3f(&t, obj, targ);
   pl2VectorScale3f(&v, &t, distance / pl2VectorLength3f(&t));
   pl2VectorAdd3f(&t, &t, &v);
   pl2VectorAdd3f(obj, &t, targ);
}
