#ifndef KJ_PLAYSCALE_SCALEDEF_H_
#define KJ_PLAYSCALE_SCALEDEF_H_

//definition octaves
#define OCT1    0x00
#define OCT2    0x01
#define OCT3    0x02
#define OCT4    0x03
#define OCT5    0x04
#define OCT6    0x05
#define OCT7    0x06
#define OCT8    0x07

//definition scales
#define C   0x00
#define CS  0x01
#define D   0x02
#define DS  0x03
#define E   0x04
#define F   0x05
#define FS  0x06
#define G   0x07
#define GS  0x08
#define A   0x09
#define AS  0x0A
#define B   0x0B
#define REST   0x0C

/*octave1*/
#define C1  (OCT1 << 4) | C
#define CS1 (OCT1 << 4) | CS
#define D1  (OCT1 << 4) | D
#define DS1 (OCT1 << 4) | DS
#define E1  (OCT1 << 4) | E
#define F1  (OCT1 << 4) | F
#define FS1 (OCT1 << 4) | FS
#define G1  (OCT1 << 4) | G
#define GS1 (OCT1 << 4) | GS
#define A1  (OCT1 << 4) | A
#define AS1 (OCT1 << 4) | AS
#define B1  (OCT1 << 4) | B

/*octave2*/
#define C2  (OCT2 << 4) | C
#define CS2 (OCT2 << 4) | CS
#define D2  (OCT2 << 4) | D
#define DS2 (OCT2 << 4) | DS
#define E2  (OCT2 << 4) | E
#define F2  (OCT2 << 4) | F
#define FS2 (OCT2 << 4) | FS
#define G2  (OCT2 << 4) | G
#define GS2 (OCT2 << 4) | GS
#define A2  (OCT2 << 4) | A
#define AS2 (OCT2 << 4) | AS
#define B2  (OCT2 << 4) | B

/*octave3*/
#define C3  (OCT3 << 4) | C
#define CS3 (OCT3 << 4) | CS
#define D3  (OCT3 << 4) | D
#define DS3 (OCT3 << 4) | DS
#define E3  (OCT3 << 4) | E
#define F3  (OCT3 << 4) | F
#define FS3 (OCT3 << 4) | FS
#define G3  (OCT3 << 4) | G
#define GS3 (OCT3 << 4) | GS
#define A3  (OCT3 << 4) | A
#define AS3 (OCT3 << 4) | AS
#define B3  (OCT3 << 4) | B

/*octave4: reference*/
#define C4  (OCT4 << 4) | C
#define CS4 (OCT4 << 4) | CS
#define D4  (OCT4 << 4) | D
#define DS4 (OCT4 << 4) | DS
#define E4  (OCT4 << 4) | E
#define F4  (OCT4 << 4) | F
#define FS4 (OCT4 << 4) | FS
#define G4  (OCT4 << 4) | G
#define GS4 (OCT4 << 4) | GS
#define A4  (OCT4 << 4) | A
#define AS4 (OCT4 << 4) | AS
#define B4  (OCT4 << 4) | B

/*octave5*/
#define C5  (OCT5 << 4) | C
#define CS5 (OCT5 << 4) | CS
#define D5  (OCT5 << 4) | D
#define DS5 (OCT5 << 4) | DS
#define E5  (OCT5 << 4) | E
#define F5  (OCT5 << 4) | F
#define FS5 (OCT5 << 4) | FS
#define G5  (OCT5 << 4) | G
#define GS5 (OCT5 << 4) | GS
#define A5  (OCT5 << 4) | A
#define AS5 (OCT5 << 4) | AS
#define B5  (OCT5 << 4) | B

/*octave6*/
#define C6  (OCT6 << 4) | C
#define CS6 (OCT6 << 4) | CS
#define D6  (OCT6 << 4) | D
#define DS6 (OCT6 << 4) | DS
#define E6  (OCT6 << 4) | E
#define F6  (OCT6 << 4) | F
#define FS6 (OCT6 << 4) | FS
#define G6  (OCT6 << 4) | G
#define GS6 (OCT6 << 4) | GS
#define A6  (OCT6 << 4) | A
#define AS6 (OCT6 << 4) | AS
#define B6  (OCT6 << 4) | B

/*octave7*/
#define C7  (OCT7 << 4) | C
#define CS7 (OCT7 << 4) | CS
#define D7  (OCT7 << 4) | D
#define DS7 (OCT7 << 4) | DS
#define E7  (OCT7 << 4) | E
#define F7  (OCT7 << 4) | F
#define FS7 (OCT7 << 4) | FS
#define G7  (OCT7 << 4) | G
#define GS7 (OCT7 << 4) | GS
#define A7  (OCT7 << 4) | A
#define AS7 (OCT7 << 4) | AS
#define B7  (OCT7 << 4) | B

/*octave8*/
#define C8  (OCT8 << 4) | C
#define CS8 (OCT8 << 4) | CS
#define D8  (OCT8 << 4) | D
#define DS8 (OCT8 << 4) | DS
#define E8  (OCT8 << 4) | E
#define F8  (OCT8 << 4) | F
#define FS8 (OCT8 << 4) | FS
#define G8  (OCT8 << 4) | G
#define GS8 (OCT8 << 4) | GS
#define A8  (OCT8 << 4) | A
#define AS8 (OCT8 << 4) | AS
#define B8  (OCT8 << 4) | B

#endif /* KJ_PLAYSCALE_SCALEDEF_H_ */