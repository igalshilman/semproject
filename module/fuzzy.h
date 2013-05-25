
#ifndef __SCHED_FUZZY_H__
#define __SCHED_FUZZY_H__

struct sched_fuzzy_point {
  int x;
  int y;
};

struct sched_fuzzy_set {
  struct sched_fuzzy_point a;
  struct sched_fuzzy_point b;
  struct sched_fuzzy_point c;
  struct sched_fuzzy_point d;
};

static inline int fuzzy_xof(struct sched_fuzzy_point *p)
{
  return p->x;
}

static inline int fuzzy_yof(struct sched_fuzzy_point *p)
{
  return p->y;
}

static inline int fuzzy_between(struct sched_fuzzy_point *p1,
    struct sched_fuzzy_point *p2,
    unsigned int x)
{
  return (fuzzy_xof(p1) <= x && x <= fuzzy_xof(p2));
}

static inline int fuzzy_eval_fx(struct sched_fuzzy_point *p1,
    struct sched_fuzzy_point *p2,
    unsigned int x)
{
  int x1,x2,y1,y2;
  long int slope ;
  x1 = fuzzy_xof(p1); y1 = fuzzy_yof(p1);
  x2 = fuzzy_xof(p2); y2 = fuzzy_yof(p2);
  slope = (y2 - y1 ) / (x2 - x1);
  return (slope * (x - x1)) + y1;
}

static int fuzzy_degree(struct sched_fuzzy_set *fs,unsigned int x)
{
  if (x <= fuzzy_xof(&fs->a))
    return fuzzy_yof(&fs->a);

  if (fuzzy_xof(&fs->d) <= x)
    return fuzzy_yof(&fs->d);

  if (fuzzy_between(&fs->a,&fs->b,x))
    return fuzzy_eval_fx(&fs->a,&fs->b,x);

  if (fuzzy_between(&fs->b,&fs->c,x))
    return fuzzy_eval_fx(&fs->b,&fs->c,x);

  if (fuzzy_between(&fs->c,&fs->d,x))
    return fuzzy_eval_fx(&fs->c,&fs->d,x);

  return 0;
}

static inline int fuzzy_and(struct sched_fuzzy_set *s1,
    struct sched_fuzzy_set *s2,
    unsigned int x)
{
  int mu1 = fuzzy_degree(s1,x);
  int mu2 = fuzzy_degree(s2,x);
  if (mu1 < mu2)
    return mu1;
  return mu2;
}

static inline int fuzzy_or(struct sched_fuzzy_set *s1,
    struct sched_fuzzy_set *s2,
    unsigned int x)
{
  int mu1 = fuzzy_degree(s1,x);
  int mu2 = fuzzy_degree(s2,x);
  if (mu1 > mu2)
    return mu1;
  return mu2;
}


#define DECLARE_INIT_FS(name,a1,a2,b1,b2,c1,c2,d1,d2)  \
  struct sched_fuzzy_set name  = {.a = {.x = a1, .y = a2}, \
    .b = {.x = b1, .y = b2}, \
    .c = {.x = c1, .y = c2}, \
    .d = {.x = d1, .y = d2}}

#endif

