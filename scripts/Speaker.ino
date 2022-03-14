#include "BluetoothA2DPSource.h"
#include <math.h> 

#define c3_frequency  130.81
#define c4_frequency  261.63 
#define a4_frequency  440.00

BluetoothA2DPSource a2dp_source;

int32_t get_data_channels(Channels *channels, int32_t channel_len, bool loop=false) {
    static double m_time = 0.0;
    double m_amplitude = 10000.0;  // -32,768 to 32,767
    double m_deltaTime = 1.0 / 44100.0;
    double m_phase = 0.0;
    double double_Pi = PI * 2.0;
    // fill the channel data
    for (int sample = 0; sample < channel_len; ++sample) {
        double angle = double_Pi * c4_frequency * m_time + m_phase;
        channels[sample].channel1 = m_amplitude * sin(angle);
        channels[sample].channel2 = channels[sample].channel1;
        m_time += m_deltaTime;
    }
    return channel_len;
}





void setup() {
  
  a2dp_source.start("SoundCore mini", get_data_channels);  
}

void loop() {
}
