#include "WaveGen.h"
// Constructor taking arguments for sample rate, wavetable data and phase
GenerateWavetable::GenerateWavetable(float sampleRate, std::vector<float>& wavetable, float phase)
{
	setup(sampleRate, wavetable, phase);
} 

// Setting up wavetable data, phase and sampleRate to be used in functions & their calls
void GenerateWavetable::setup(float sampleRate, std::vector<float>& wavetable, float phase)
{
	// It's faster to multiply than to divide on most platforms, so we save the inverse
	// of the sample rate for use in the phase calculation later
	inverseSampleRate_ = 1.0f / sampleRate;
	
	// Assign parameters 
	sampleRate_ = sampleRate;
	
	wavetable_ = wavetable;
	
	phase_ = phase;
	
	// Calculates the phase increment for a waveform table of a given size and sample rate
	phaseIncrement_ = (wavetable_.size() * inverseSampleRate_); 
	
}

// Calculates poly_blep (Martin Finke,(no date))
float GenerateWavetable::poly_blep(float t /*phase*/, float dt /*phaseHalfIncrement*/) 
{
	float32x4_t t_neon = vdupq_n_f32(t); float32x4_t dt_neon = vdupq_n_f32(dt); float32x4_t one_neon = vdupq_n_f32(1.0f);

float32x4_t t_lt_dt_mask = vcltq_f32(t_neon, dt_neon);
float32x4_t t_gt_1_minus_dt_mask = vcgtq_f32(t_neon, vsubq_f32(one_neon, dt_neon));

// Calculate t / dt
float32x4_t t_div_dt = vdivq_f32(t_neon, dt_neon);

// Calculate t + t - t * t - 1.0f
float32x4_t t_minus_t_squared_minus_one = vsubq_f32(vmulq_f32(t_div_dt, t_neon), one_neon);
float32x4_t result_lt_dt = vaddq_f32(vaddq_f32(t_neon, t_neon), t_minus_t_squared_minus_one);

// Calculate (t - 1.0f) / dt
float32x4_t t_minus_one_div_dt = vdivq_f32(vsubq_f32(t_neon, one_neon), dt_neon);

// Calculate t * t + t + t + 1.0f
float32x4_t t_squared_plus_t_plus_t_plus_one = vaddq_f32(vmulq_f32(t_minus_one_div_dt, t_minus_one_div_dt), vaddq_f32(t_minus_one_div_dt, t_minus_one_div_dt));
float32x4_t result_gt_1_minus_dt = vaddq_f32(t_squared_plus_t_plus_t_plus_one, one_neon);

// Apply masks to select the results based on conditions
float32x4_t result_masked_lt_dt = vbslq_f32(t_lt_dt_mask, result_lt_dt, vdupq_n_f32(0.0f));
float32x4_t result_masked_gt_1_minus_dt = vbslq_f32(t_gt_1_minus_dt_mask, result_gt_1_minus_dt, vdupq_n_f32(0.0f));

// Select the final result based on the conditions
float32x4_t result = vaddq_f32(result_masked_lt_dt, result_masked_gt_1_minus_dt);

// Extract the result value from the NEON register and return it
return vgetq_lane_f32(result, 0);
}

float GenerateWavetable::prompt_WaveType(unsigned int waveNumber, float n)
{
	// Set values for poly_blep
	float dt = phaseIncrement_ / wavetable_.size();
	
    float t = phase_;
    
    // Initalise value for further use
    float value = 0.0f;
    
    // Use argument waveNumber to change the type of the wave 
    switch (waveNumber)
    {
        case 1:
        //Sine
            value = (sinf(2.0f * M_PI * (float)n / (float)wavetable_.size() + phase_));
            break;
        case 2:	
        //Triangle
            value = (2.0f * fabs(-1.0f + 2.0f * (float)n / (float)(wavetable_.size() - 1))-0.5f)+ phase_;
            break;
        case 3: 
        //Square
            value = (sinf(2.0f * M_PI * (float)n / (float)wavetable_.size() + phase_));
            value = value >= 0.0f ? 1.0f : -1.0f;
            break;
        case 4: 
        //Sawtooth
            value = (-1.0f + 2.0f * (float)n / (float)(wavetable_.size() - 1)+ phase_);
            break;
    }
    // Return the wave type and Subtract poly_blep
    return  value -= poly_blep(t, dt);
}

// Uses the wavetable_ defined from the constuctor to assign a wave type to wavetable_ then adds the 
// wavetable_ to <Wavetable*> and sends the <Wavetable*> back to render to be used 
std::vector<Wavetable*> GenerateWavetable::prompt_Modulator(std::vector<Wavetable*> gOscillators, unsigned int waveNumber)
{
	for(unsigned int n = 0; n < wavetable_.size(); n++) 
    {
        wavetable_[n]= prompt_WaveType(waveNumber, n);
    }
    Wavetable* oscillators = new Wavetable(sampleRate_, wavetable_, phase_); 
    
	gOscillators.push_back(oscillators); 

	// Delete memory without -1 there is a bus error
    for (unsigned int i = 0; i < gOscillators.size(); i++)
    {
        delete gOscillators[i];
    }
	
    return gOscillators;
}

// Uses the wavetable_ defined from the constuctor to assign a wave type to wavetable_ then returns value
std::vector<float> GenerateWavetable::prompt_Harmonics(unsigned int waveNumber)
{
	  for(unsigned int n = 0; n < wavetable_.size(); n++) 
    {
        wavetable_[n]= prompt_WaveType(waveNumber, n);
    }
    return wavetable_;
}



