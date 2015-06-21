//
//  core.cpp
//  TraceRay
//
//  Created by LazyLie on 15/6/21.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#include "core.h"
const char RECT = 'r';
const char BALL = 'b';

CollideInfo Ball::collide(const Ray &r) {
  CollideInfo info;
  info.distance = -1;
  Vector v = r.position - position;
  
  if (r.inside) {
    if (norm(r.position - position) > radius + EPS) return info;
    double tmp = sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius);
    assert(tmp >= -EPS);
    if (tmp < 0) tmp = 0;
    info.distance = -innerProduct(r.direction, v) + sqrt(tmp);
    assert(info.distance >= -EPS);
    if (info.distance < 0) info.distance = 0;
    info.normal = position - (r.position + info.distance * r.direction);
    info.normal = info.normal / norm(info.normal);
    info.index = 1.0 / attribute.index;
    return info;
  } else {
    if (innerProduct(v, r.direction) > 0) return info;
    
    if (sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius) < 0) return info;
    info.distance = -innerProduct(r.direction, v) - sqrt(sqr(innerProduct(r.direction, v)) - innerProduct(v, v) + sqr(radius));
    info.normal = r.position + info.distance * r.direction - position;
    info.normal = info.normal / norm(info.normal);
    info.index = attribute.index;
    return info;
  }
}

CollideInfo Rect::collide(const Ray &r) {
  CollideInfo info;
  info.distance = -1;
  
  Vector v = position - r.position;
  Vector n = crossProduct(dx, dy);
  n = n / norm(n);
  
  if (r.inside) n = -n;
  
  if (innerProduct(n, r.direction) >= 0) return info;
  
  info.distance = innerProduct(n, v) / innerProduct(r.direction, n);
  if (info.distance < EPS) {
    info.distance = -1;
    return info;
  }
  
  Vector p = r.position + info.distance * r.direction;
  
  double lx = norm(dx);
  double ly = norm(dy);
  double ax = innerProduct(p - position, dx / lx);
  double ay = innerProduct(p - position, dy / ly);
  if (ax < 0 || ax > lx || ay < 0 || ay > ly) {
    info.distance = -1;
    return info;
  }
  info.normal = n;
  info.index = r.inside ? (1.0 / attribute.index) : attribute.index;
  
  return info;
}

Ray reflect(const Ray &in, const Vector &position, const Vector &normal) {
  Ray ref;
  ref.inside = in.inside;
  ref.position = position;
  ref.direction = in.direction - 2 * innerProduct(in.direction, normal) * normal;
  return ref;
}

Ray transparent(const Ray &in, const Vector &position, const Vector &normal, const double index) {
  Ray tra;
  double cosTheta = 1 - (1 - sqr(innerProduct(in.direction, normal))) / sqr(index);
  if (cosTheta >= 0 && cosTheta <= 1) {
    cosTheta = sqrt(cosTheta);
    tra.position = position;
    tra.direction = 1 / index * in.direction - (1 / index * innerProduct(in.direction, normal) + cosTheta) * normal;
    tra.direction = tra.direction / norm(tra.direction);
    tra.inside = !in.inside;
  }
  return tra;
}

void insertBox(std::vector< std::pair<char, void*> > &item, const Vector &p, const Vector &x, const Vector &y, const Vector &z, const Attribute &attr) {
  Rect *rect = new Rect();
  rect->attribute = attr;
  rect->position = p;
  rect->dx = y;
  rect->dy = x;
  item.push_back(make_pair(RECT, rect));
  
  rect = new Rect();
  rect->attribute = attr;
  rect->position = p;
  rect->dx = x;
  rect->dy = z;
  item.push_back(make_pair(RECT, rect));
  
  rect = new Rect();
  rect->attribute = attr;
  rect->position = p;
  rect->dx = z;
  rect->dy = y;
  item.push_back(make_pair(RECT, rect));
  
  Vector pp = p + x + y + z;
  rect = new Rect();
  rect->attribute = attr;
  rect->position = pp;
  rect->dx = -x;
  rect->dy = -y;
  item.push_back(make_pair(RECT, rect));
  
  rect = new Rect();
  rect->attribute = attr;
  rect->position = pp;
  rect->dx = -z;
  rect->dy = -x;
  item.push_back(make_pair(RECT, rect));
  
  rect = new Rect();
  rect->attribute = attr;
  rect->position = pp;
  rect->dx = -y;
  rect->dy = -z;
  item.push_back(make_pair(RECT, rect));
  
}
