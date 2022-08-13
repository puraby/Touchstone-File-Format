# Touchstone-File-Format
A Touchstone file is a standard file format used by vector network analyzers to store measurement results. It is also a format that lots of software can read, such as simulators. If you use a VNA, then you need to understand the Touchstone file format. The format is described formally in the Touchstone specification.

Touchstone files have the extension of .sNp, where N is the number of ports. So measurement results of a one-port device such as a Yagi-Uda antenna could be stored in a file called yagi-uda.s1p. Data on a two-port device, such as an attenuator, might be stored in a file called attenuator.s2p. Data on a 3-port device, such as a directional coupler, might be stored in a file called directional-coupler.s3p.

All Kirkby Microwave coaxial calibration and verification kits come with an attenuator which has measured data which is stored in a Touchstone file. So it is important to understand the Touchstone file format, especially the .s2p format.

All Touchstone files much have:

An "option line" which describes the format of the data which follows the "option line".
The data, which may be just one line long, but typically there are hundreds or thousands of data lines, as VNAs are usually used to sweep a range of frequencies.
One port (.s1p) Touchstone file.
A really simple Touchstone file for a one-port device might be:

# MHz S DB R 50
143.40000 -15.91406 100.92188
The first line, the "option line", describes the format of the data to follow:

The MHz indicates that the data is stored at various frequencies in MHz. (Legal values are GHz, MHz, KHz and Hz.)
The S indicates that the data points(s) are Scattering parameters. (Other legal values are Y, Z, H or G, as described in the Touchstone specification )
The DB indicates the data are in decibels and angle, where dB = 20*log10|magnitude| and angles are in degrees.
The R indicates there's a reference impedance - if this is omitted, an impedance of 50 Ω is assumed.
The 50 indicates the reference impedance is 50 Ω, which is the most common, and need not be present, but it usually is for clarity.
The second line, which contains data, indicates that at 143.4 MHz, the magnitude of S11 is -15.91406 dB and the phase angle 100.92188 degrees. (The number of decimal places shown is far more than what are justified, but are just the numbers indicated by the VNA).

In addition to the bare minimum information, most Touchstone files will have:

One or more comment lines, which typically contain the date and measurement conditions.
Several lines of data, not just one.
So a more typical one-port Touchstone .s1p file might be:

! HEWLETT PACKARD,8720D,0,7.74  
! Date = 11 Aug 2016
! Time = 15:12:03
# MHz S DB R 50
143.40000 -15.91406 100.92188
143.41000 -15.90332 100.10547
143.42000 -15.91260 99.08984
143.43000 -15.87842 98.34375
143.44000 -15.89844 97.48047
143.45000 -15.93262 96.71094
143.46000 -15.87012 95.83203
143.47000 -15.85400 95.08203
The file will generally be much longer, and often contains hundreds of lines of data.

Two port (.s2p) Touchstone file.
A two-port .s2p Touchstone file, which has the data in S-parameter format, has data on the 4 S-parameters

S11
S21
S12
S22
Since each S-parameter has two values (magnitude and phase), there are an extra 3x6=6 columns of data making 3+6=9 columns in total. A typical 2-port .s2p Touchstone file must, like the .s1p file, have one "option line", and at least one "data line". Like a typical 1-port Touchstone file, there will usually be comments and many data lines. So a typical 2-port .s2p file might be:

! HEWLETT PACKARD,8720D,0,7.74  
! Date = 31 Aug 2013
! Time = 18:37:05
! Start frequency = 0.050000000 GHz
! Stop frequency  = 6.000000000 GHz
# MHz S DB R 50
50.00 -61.89 -16.52 -29.73 -2.63 -29.74 -2.63 -60.01 39.32
53.71 -63.77 -20.76 -29.75 -2.89 -29.74 -3.07 -59.57 37.52
57.43 -62.44 -4.62 -29.71 -3.19 -29.76 -3.09 -59.75 34.60
61.15 -60.24 -1.19 -29.73 -3.16 -29.76 -3.47 -60.52 37.78
64.87 -59.28  6.90 -29.73 -3.54 -29.71 -3.72 -60.82 41.33
The format of the data is:

Column 1 is the frequency - in this case in MHz, since the "option line" contains "MHz".
Columns 2 and 3 are the magnitude and phase of S11 - in this case, the magnitude is in dB and the phase in degrees since the "option line" says contains "DB".
Columns 4 and 5 are the magnitude and phase of S21 - in this case the magnitude is in dB and the phase in degrees since the option line says that.
Columns 6 and 7 are the magnitude and phase of S12 - in this case the magnitude is in dB and the phase in degrees since the option line says that.
Columns 8 and 9 are the magnitude and phase of S22 - in this case the magnitude is in dB and the phase in degrees since the option line says that.
Column 1 is always the frequency, and the other S-parameters are listed in the order S11, S21, S12, and S22, with magnitudes given before phases. So the order of the data is:

frequency magS11 angS11 magS21 angS21 magS12 angS12 magS22 angS22
The file will generally be much longer, and often contains hundreds of lines of data.

3-port (.s3p) and higher (e.g. .s4p, .s5p) Touchstone files.
Although Kirkby Microwave calibration kits can be used to calibrate VNAs with many ports, for the purposes of using the kit, and the verification attenuator we provide, there's no need to understand Touchstone files with more than 2 ports.

The data in 3 and higher port Touchstone files are stored differently to .s1p and .s2p files. There are not the 19 columns you might expect on a 3 port file.
