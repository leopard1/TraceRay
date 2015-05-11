//
//  core.h
//  TraceRay
//
//  Created by LazyLie on 15/5/10.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__core__
#define __TraceRay__core__

#include <stdio.h>
#include "foundation.h"

extern const double EPS;

class Node {
    fvector3D position;
    
public:
    fvector3D getPosition() const;
    void setPosition(const fvector3D &p);
    virtual double getCollide(const Ray &r) const = 0;
    virtual bool isSurface(const fvector3D &p) const = 0;
    virtual fvector3D getNormalVector(const fvector3D &p) const = 0;
};


#endif /* defined(__TraceRay__core__) */
