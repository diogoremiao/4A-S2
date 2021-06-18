import numpy as np
import os
import librosa
import librosa.display
import matplotlib.pyplot as plt


# All the functions
eps = np.finfo(float).eps

# Default Values
N_FFT = 2048
FRAME_LEN = 2048
HOP_LEN = 512
WIN_LEN = 2048
WINDOW = 'hann'
sr = 22050


def simple_log_attack_time(x, f_s):
    """
    computes the log-attack time from the waveform (time from 20% to 90%)
      Args:
        x: waveform 
        f_s: sample rate of audio data
      Returns:
        lat (in secs)
    """
    def find_nearest_arg(array, value):
        array = np.asarray(np.squeeze(array))
        idx = (np.abs(array - value)).argmin()
        return idx

    rms = librosa.feature.rms(y=x, frame_length=FRAME_LEN, hop_length=HOP_LEN)
    e20_pos = find_nearest_arg(rms, 0.2*np.max(rms))
    e90_pos = find_nearest_arg(rms, 0.9*np.max(rms))
    e20_time = e20_pos * HOP_LEN/sr
    e90_time = e90_pos * HOP_LEN/sr
    if e20_time > e90_time:
	    e20_time = 0
    
    lat = np.log(e90_time - e20_time + eps)
    return lat


def temporal_centroid(x, f_s):
    """
    adapted from https://www.audiocontentanalysis.org/code/audio-features/spectral-centroid-2/
    computes the temporal centroid from the waveform
      Args:
        x: waveform 
        f_s: sample rate of audio data
      Returns:
        vtc temporal centroid (in secs)
    """
    x=np.power(x,2)
    norm = x.sum(axis=0, keepdims=True)
    norm[norm == 0] = 1
    vtc = np.dot(np.arange(0, x.shape[0]), x) / norm
    # convert from index to sec
    vtc = vtc / f_s
    # if input is a spectrum, output scaler else if spectrogram, output 1d array
    vtc = np.squeeze(vtc)
    return vtc


def spectral_flux(X, f_s):
    """
    adapted from https://www.audiocontentanalysis.org/code/audio-features/spectral-flux-2/
    computes the spectral flux from the magnitude spectrum
      Args:
        X: spectrogram (dimension FFTLength X Observations)
        f_s: sample rate of audio data
      Returns:
        vsf spectral flux
    """
    isSpectrum = X.ndim == 1
    if isSpectrum:
        X = np.expand_dims(X, axis=1)
    # difference spectrum (set first diff to zero)
    X = np.c_[X[:, 0], X]
    afDeltaX = np.diff(X, 1, axis=1)
    # flux
    vsf = np.sqrt((afDeltaX**2).sum(axis=0)) / X.shape[0]
    return np.squeeze(vsf) if isSpectrum else vsf.real


def inst_freq_descriptors(y, sr, n_fft=N_FFT, hop_length=HOP_LEN, window=WINDOW, win_length=None):
    # Spectral Descriptors
    spec_centroid = librosa.feature.spectral_centroid(y=y, sr=sr, n_fft=n_fft, hop_length=hop_length, win_length=win_length, window=window)
    spec_bandwidth = librosa.feature.spectral_bandwidth(y=y, sr=sr, n_fft=n_fft, hop_length=hop_length, win_length=win_length, window=window)
    spec_flux = spectral_flux(librosa.stft(y, n_fft=n_fft, hop_length=hop_length, win_length=win_length), sr)
    spec_flatness = librosa.feature.spectral_flatness(y=y, n_fft=n_fft, hop_length=hop_length, win_length=win_length, window=window)

    return spec_centroid, spec_bandwidth, spec_flux, spec_flatness


def inst_time_descriptors(y, sr, frame_length=FRAME_LEN, hop_length=HOP_LEN):
    # Instantaneous Time Descriptors
    rms = librosa.feature.rms(y=y, frame_length=frame_length, hop_length=hop_length)
    zcr = librosa.feature.zero_crossing_rate(y=y, frame_length=frame_length, hop_length=hop_length)

    return rms, zcr


def global_time_descriptors(y, sr):
    # Global Time Descriptors
    tc = temporal_centroid(y, sr)
    lat = simple_log_attack_time(y, sr)
    # Normalized descriptors (normalized by duration of sound)
    ntc = tc/librosa.get_duration(y=y, sr=sr)
    nlat = lat/librosa.get_duration(y=y, sr=sr)
    return tc, lat, ntc, nlat

def sound_duration(y,sr):
    #Compute the duration (in seconds) of an audio time series, feature matrix, or filename
    duration=librosa.get_duration(y=y,sr=sr)
    return duration

def calc_statistical_features(arr):
    result = np.zeros(5)
    result[0] = np.mean(arr.real)
    result[1] = np.var(arr.real)
    result[2] = np.median(arr.real)
    result[3] = np.min(arr.real)
    result[4] = np.max(arr.real)
    result = np.nan_to_num(result)
    return result


def plot_frequency_descriptors(y, Fs):
    # Get Discrete FT
    D = librosa.stft(y)  # STFT of y
    # Get Spectrogram in dB
    S_db = librosa.amplitude_to_db(np.abs(D), ref=np.max)
    fig, ax = plt.subplots(2, sharex=True)
    img = librosa.display.specshow(S_db, x_axis='time', y_axis='linear', ax=ax[1])
    spec_centroid, spec_bw, spec_flux, spec_flat = inst_freq_descriptors(y, Fs)
    times = librosa.times_like(spec_centroid)

    ax[1].plot(times, spec_centroid.T, label='spec_centroid', color='w')
    ax[1].plot(times, spec_bw.T, label='spec_bw', color='b')
    ax[1].fill_between(times, spec_centroid[0] - spec_bw[0], spec_centroid[0] + spec_bw[0], alpha=0.5, label='Centroid +- bandwidth')
    #ax[1].legend()
    #this is giving an error
    
    # Plot in a different axis because it is in a different order of magnitude
    # and can't be seen in the other axis
    ax[0].plot(times, spec_flux, label='spec_flux', color='r')
    ax[0].plot(times, spec_flat.T, label='spec_flat', color='g')
    ax[0].legend()
    return True


def plot_time_descriptors(y, Fs):
    fig, ax = plt.subplots(1)
    img = librosa.display.waveplot(y, x_axis='time', ax=ax)
    rms, zcr = inst_time_descriptors(y, Fs)
    times = librosa.times_like(rms)
    ax.plot(times, rms.T, label='rms', color='b')
    ax.plot(times, zcr.T, label='zcr', color='r')
    ax.legend(loc='upper right')
    return True


def main():

    fn_wav = os.path.join('.', 'Sounds', 'vln_g_G3_12.wav')
    x, Fs = librosa.load(fn_wav)

    # Time descriptors
    rms, zcr = inst_time_descriptors(x, Fs)
    tc, lat, ntc, nlat = global_time_descriptors(x, Fs)
    plot_time_descriptors(x,Fs)
    #print global descriptors
    print("Temporal Centroid: ", tc)
    print("Temporal Log Attack Time: ", lat)

    print("Normalized Temporal Centroid: ", ntc)
    print("Normalized Temporal Log Attack Time: ", nlat)

    # Frequency descriptors
    spec_centroid, spec_bw, spec_flux, spec_flat = inst_freq_descriptors(x, Fs)
    plot_frequency_descriptors(x, Fs)

    #Effective duration (is it really?)
    dd = sound_duration(x, Fs)
    print("Effective Duration", dd)

    # We can obtain the statistics per sound of the instantaneous descriptors
    # This is just an example. You can add or use whatever statistic measure you think is better

    # RMS stats
    stats_rms = calc_statistical_features(rms)
    print("RMS Stats")
    print(f'mean:{stats_rms[0]:.3f}  var:{stats_rms[1]:.3f}  median:{stats_rms[2]:.3f}  min:{stats_rms[3]:.3f}  max:{stats_rms[4]:.3f}')

    # ZCR stats
    stats_zcr = calc_statistical_features(zcr)
    print("ZCR Stats")
    print(f'mean:{stats_zcr[0]:.3f}  var:{stats_zcr[1]:.3f}  median:{stats_zcr[2]:.3f}  min:{stats_zcr[3]:.3f}  max:{stats_zcr[4]:.3f}')

    # Spec Centroid stats
    stats_sc = calc_statistical_features(spec_centroid)
    print("Spectral Centroid Stats")
    print(f'mean:{stats_sc[0]:.3f}  var:{stats_sc[1]:.3f}  median:{stats_sc[2]:.3f}  min:{stats_sc[3]:.3f}  max:{stats_sc[4]:.3f}')

    # Spec Spread stats
    stats_ss = calc_statistical_features(spec_bw)
    print("Spectral Spread Stats")
    print(f'mean:{stats_ss[0]:.3f}  var:{stats_ss[1]:.3f}  median:{stats_ss[2]:.3f}  min:{stats_ss[3]:.3f}  max:{stats_ss[4]:.3f}')

    # Spec Flux stats
    stats_sflux = calc_statistical_features(spec_flux)
    print("Spectral Flux Stats")
    print(f'mean:{stats_sflux[0]:.3f}  var:{stats_sflux[1]:.3f}  median:{stats_sflux[2]:.3f}  min:{stats_sflux[3]:.3f}  max:{stats_sflux[4]:.3f}')

    # Spec Flatness stats
    stats_sflat = calc_statistical_features(spec_flat*1000)
    print("Spectral Flatness Stats")
    print(f'mean:{stats_sflat[0]:.3f}  var:{stats_sflat[1]:.3f}  median:{stats_sflat[2]:.3f}  min:{stats_sflat[3]:.3f}  max:{stats_sflat[4]:.3f}')


    rms, zcr = inst_time_descriptors(x, Fs, frame_length=1000, hop_length=200)
    spec_centroid, spec_bw, spec_flux, spec_flat = inst_freq_descriptors(x, sr, n_fft=1000, hop_length=200)

    #final plot
    plt.show()




if __name__ == "__main__":
    main()