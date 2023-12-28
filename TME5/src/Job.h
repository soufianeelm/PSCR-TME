#pragma once
#include "Vec3D.h"
#include "Rayon.h"
#include "Scene.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>
#include <random>

namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

// Job concret : exemple


class PixelJob : public Job {
	int calcul (const Scene::screen_t & screen, std::vector<Vec3D> lights, Color * pixels) {
		// le point de l'ecran par lequel passe ce rayon
		auto & screenPoint = screen[y][x];
		// le rayon a inspecter
		Rayon  ray(scene.getCameraPos(), screenPoint);

		int targetSphere = findClosestInter(scene, ray);

		if (targetSphere == -1) {
			// keep background color
			continue ;
		} else {
			const Sphere & obj = *(scene.begin() + targetSphere);
			// pixel prend la couleur de l'objet
			Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
			// le point de l'image (pixel) dont on vient de calculer la couleur
			Color & pixel = pixels[y*(*scene).getHeight() + x];
			// mettre a jour la couleur du pixel dans l'image finale.
			pixel = finalcolor;
		}
	}
	const Scene::screen_t &  arg1;
	std::vector<Vec3D>  arg2;
	Color * arg3;
public :
	PixelJob(auto * arg1, auto * arg2) : arg1(arg1), arg2(arg2), arg3(arg3) {}
	void run () {
		calcul(arg1, arg2, arg3);
	}
	~SleepJob(){}
};


}
