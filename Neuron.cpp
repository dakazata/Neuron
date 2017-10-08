#include <iostream>
#include "Neuron.h"
#include <cmath>

//constants
double THRESHOLD_POT(30);
double TSTEP(1);        //in ms
double REFR_PERIOD(10);
double V_RESET(10);
//double TSTART(0.0);
//double TSTOP (6000.0);  

//constructor
Neuron::Neuron(double pot, double res, double cap, bool ref, double current)
: membr_potential(pot), membr_resistance(res), membr_capacity(cap),
  refractory(ref), current_ext(current)
{}
		
//get et set
double Neuron::getMembPotential() const
{
	return membr_potential;
}

int Neuron::getNbSpikes() const
{
	return nb_spikes;
}

std::vector<double> Neuron::getSpikeTimes() const
{
	return spike_times;
}

void Neuron::setRefractory(bool ref)
{
	refractory = ref;
}
		
//update
void Neuron::update(double start, double stop, double current)
{
	//calculate constants for the equation
	double tao = membr_capacity * membr_resistance;
	std::cout << "tao: " << tao << std::endl;
	double c1 = exp(-TSTEP/tao);
	double c2 = membr_resistance * (1- c1);
	double simtime = start;
	double reftime_countdown(REFR_PERIOD);
	while(simtime < stop)
	{
		std::cout << "simtime: " << simtime << std::endl;
		std::cout << "potential : " << membr_potential << std::endl;
		current_ext = current;
		if (refractory)
		{
			membr_potential = 0.0;
			//manmage the refarctory period - decreases every simtime
			reftime_countdown-- ;
			if(reftime_countdown <= 0.0)
			{
				//when ref period is over we set refractory to true
				setRefractory(false);
				reftime_countdown = REFR_PERIOD;
				membr_potential = V_RESET;
			}
		} else if (membr_potential > THRESHOLD_POT)
		{
			addSpikeTime(simtime);
			setRefractory(true);
		}
		
		//membrane equation
		membr_potential = (c1 * membr_potential) + (current_ext * c2);
		
		simtime += TSTEP;
	}
}

//add Spiketime
void Neuron::addSpikeTime(double newspike)
{
	spike_times.push_back(newspike);
}
	

