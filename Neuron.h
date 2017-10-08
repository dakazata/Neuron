#ifndef NEURON_H
#define NEURON_H

#include <vector>
//#include <array>
//#include "Time.h"                     //avoir une classe pour le temps

//declaration type temps 
//typedef std::array<int,3> Time;


class Neuron
{
	private:
		double membr_potential;
		double membr_resistance; //R = 20
		double membr_capacity ;  //C = 1
		int nb_spikes;
		std::vector<double> spike_times;
		bool refractory;               //true if the neuron is refractory 
		double current_ext;
		
	public:
		//constructor
		Neuron(double pot, double res, double cap, bool ref, double current = 0.0);
		
		//get et set
		double getMembPotential() const;
		int getNbSpikes() const;
		std::vector<double> getSpikeTimes() const;
		void setRefractory(bool);
		
		//update
		void update(double start, double stop, double current);
		
		//add Spiketime
		void addSpikeTime(double);
			
};


#endif
