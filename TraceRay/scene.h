//
//  scene.h
//  TraceRay
//
//  Created by LazyLie on 15/6/16.
//  Copyright (c) 2015年 LeonardXu. All rights reserved.
//

#ifndef __TraceRay__scene__
#define __TraceRay__scene__

#include <stdio.h>
#include "model.h"
#include "camera.h"

class Scene {
public:
  std::vector<Model> model, light;
  Camera camera;
  std::vector< std::vector<Vector> > image;
  Vector diffLight;
  
  void saveToFile(std::string filename);
  void render();
  Vector trace(Ray r, int dep);
};

#endif /* defined(__TraceRay__scene__) */
