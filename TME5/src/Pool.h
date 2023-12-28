#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize): queue(qsize) {};
	void start (int nbthread) {
		for (int i=0; i<nbthread; i++) {
			threads.push_back(std::thread(poolWorker, &queue));
		}
	}
	void submit (Job * job) {
		queue.push(job);
	}
	void stop() {
		queue.bloquant(false);
		for (auto & thread : threads){
			thread.join();
		}
	}
	~Pool() ;
	void poolWorker(Queue<Job> & queue){
		Job* j = queue.pop();
		j.run();

	}

};

}
