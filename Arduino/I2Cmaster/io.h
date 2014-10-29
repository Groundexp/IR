00001 /* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
       00002    Copyright (c) 2007 Eric B. Weddington
       00003    All rights reserved.
       00004
       00005    Redistribution and use in source and binary forms, with or without
       00006    modification, are permitted provided that the following conditions are met:
       00007
       00008    * Redistributions of source code must retain the above copyright
       00009      notice, this list of conditions and the following disclaimer.
       00010
       00011    * Redistributions in binary form must reproduce the above copyright
       00012      notice, this list of conditions and the following disclaimer in
       00013      the documentation and/or other materials provided with the
       00014      distribution.
       00015
       00016    * Neither the name of the copyright holders nor the names of
       00017      contributors may be used to endorse or promote products derived
       00018      from this software without specific prior written permission.
       00019
       00020   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
       00021   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
       00022   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
       00023   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
       00024   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
       00025   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
       00026   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
       00027   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
       00028   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
       00029   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
       00030   POSSIBILITY OF SUCH DAMAGE. */
00031
00032 /* $Id: io_8h_source.html,v 1.1.1.4 2012/01/03 16:04:22 joerg_wunsch Exp $ */
00033
00034 /** \file */
00035 /** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
       00036     \code #include <avr/io.h> \endcode
       00037
       00038     This header file includes the apropriate IO definitions for the
       00039     device that has been specified by the <tt>-mmcu=</tt> compiler
       00040     command-line switch.  This is done by diverting to the appropriate
       00041     file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
       00042     never be included directly.  Some register names common to all
       00043     AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
       00044     which is included in <tt>&lt;avr/io.h&gt;</tt>,
       00045     but most of the details come from the respective include file.
       00046
       00047     Note that this file always includes the following files:
       00048     \code
       00049     #include <avr/sfr_defs.h>
       00050     #include <avr/portpins.h>
       00051     #include <avr/common.h>
       00052     #include <avr/version.h>
       00053     \endcode
       00054     See \ref avr_sfr for more details about that header file.
       00055
       00056     Included are definitions of the IO register set and their
       00057     respective bit values as specified in the Atmel documentation.
       00058     Note that inconsistencies in naming conventions,
       00059     so even identical functions sometimes get different names on
       00060     different devices.
       00061
       00062     Also included are the specific names useable for interrupt
       00063     function definitions as documented
       00064     \ref avr_signames "here".
       00065
       00066     Finally, the following macros are defined:
       00067
       00068     - \b RAMEND
       00069     <br>
       00070     The last on-chip RAM address.
       00071     <br>
       00072     - \b XRAMEND
       00073     <br>
       00074     The last possible RAM location that is addressable. This is equal to
       00075     RAMEND for devices that do not allow for external RAM. For devices
       00076     that allow external RAM, this will be larger than RAMEND.
       00077     <br>
       00078     - \b E2END
       00079     <br>
       00080     The last EEPROM address.
       00081     <br>
       00082     - \b FLASHEND
       00083     <br>
       00084     The last byte address in the Flash program space.
       00085     <br>
       00086     - \b SPM_PAGESIZE
       00087     <br>
       00088     For devices with bootloader support, the flash pagesize
       00089     (in bytes) to be used for the \c SPM instruction.
       00090     - \b E2PAGESIZE
       00091     <br>
       00092     The size of the EEPROM page.
       00093
       00094 */
00095
00096 #ifndef _AVR_IO_H_
00097 #define _AVR_IO_H_
00098
00099 #include <avr/sfr_defs.h>
00100
00101 #if defined (__AVR_AT94K__)
00102 #  include <avr/ioat94k.h>
00103 #elif defined (__AVR_AT43USB320__)
00104 #  include <avr/io43u32x.h>
00105 #elif defined (__AVR_AT43USB355__)
00106 #  include <avr/io43u35x.h>
00107 #elif defined (__AVR_AT76C711__)
00108 #  include <avr/io76c711.h>
00109 #elif defined (__AVR_AT86RF401__)
00110 #  include <avr/io86r401.h>
00111 #elif defined (__AVR_AT90PWM1__)
00112 #  include <avr/io90pwm1.h>
00113 #elif defined (__AVR_AT90PWM2__)
00114 #  include <avr/io90pwmx.h>
00115 #elif defined (__AVR_AT90PWM2B__)
00116 #  include <avr/io90pwm2b.h>
00117 #elif defined (__AVR_AT90PWM3__)
00118 #  include <avr/io90pwmx.h>
00119 #elif defined (__AVR_AT90PWM3B__)
00120 #  include <avr/io90pwm3b.h>
00121 #elif defined (__AVR_AT90PWM216__)
00122 #  include <avr/io90pwm216.h>
00123 #elif defined (__AVR_AT90PWM316__)
00124 #  include <avr/io90pwm316.h>
00125 #elif defined (__AVR_AT90PWM81__)
00126 #  include <avr/io90pwm81.h>
00127 #elif defined (__AVR_ATmega8U2__)
00128 #  include <avr/iom8u2.h>
00129 #elif defined (__AVR_ATmega16M1__)
00130 #  include <avr/iom16m1.h>
00131 #elif defined (__AVR_ATmega16U2__)
00132 #  include <avr/iom16u2.h>
00133 #elif defined (__AVR_ATmega16U4__)
00134 #  include <avr/iom16u4.h>
00135 #elif defined (__AVR_ATmega32C1__)
00136 #  include <avr/iom32c1.h>
00137 #elif defined (__AVR_ATmega32M1__)
00138 #  include <avr/iom32m1.h>
00139 #elif defined (__AVR_ATmega32U2__)
00140 #  include <avr/iom32u2.h>
00141 #elif defined (__AVR_ATmega32U4__)
00142 #  include <avr/iom32u4.h>
00143 #elif defined (__AVR_ATmega32U6__)
00144 #  include <avr/iom32u6.h>
00145 #elif defined (__AVR_ATmega64C1__)
00146 #  include <avr/iom64c1.h>
00147 #elif defined (__AVR_ATmega64M1__)
00148 #  include <avr/iom64m1.h>
00149 #elif defined (__AVR_ATmega128__)
00150 #  include <avr/iom128.h>
00151 #elif defined (__AVR_ATmega1280__)
00152 #  include <avr/iom1280.h>
00153 #elif defined (__AVR_ATmega1281__)
00154 #  include <avr/iom1281.h>
00155 #elif defined (__AVR_ATmega1284P__)
00156 #  include <avr/iom1284p.h>
00157 #elif defined (__AVR_ATmega128RFA1__)
00158 #  include <avr/iom128rfa1.h>
00159 #elif defined (__AVR_ATmega2560__)
00160 #  include <avr/iom2560.h>
00161 #elif defined (__AVR_ATmega2561__)
00162 #  include <avr/iom2561.h>
00163 #elif defined (__AVR_AT90CAN32__)
00164 #  include <avr/iocan32.h>
00165 #elif defined (__AVR_AT90CAN64__)
00166 #  include <avr/iocan64.h>
00167 #elif defined (__AVR_AT90CAN128__)
00168 #  include <avr/iocan128.h>
00169 #elif defined (__AVR_AT90USB82__)
00170 #  include <avr/iousb82.h>
00171 #elif defined (__AVR_AT90USB162__)
00172 #  include <avr/iousb162.h>
00173 #elif defined (__AVR_AT90USB646__)
00174 #  include <avr/iousb646.h>
00175 #elif defined (__AVR_AT90USB647__)
00176 #  include <avr/iousb647.h>
00177 #elif defined (__AVR_AT90USB1286__)
00178 #  include <avr/iousb1286.h>
00179 #elif defined (__AVR_AT90USB1287__)
00180 #  include <avr/iousb1287.h>
00181 #elif defined (__AVR_ATmega64__)
00182 #  include <avr/iom64.h>
00183 #elif defined (__AVR_ATmega640__)
00184 #  include <avr/iom640.h>
00185 #elif defined (__AVR_ATmega644__) || defined (__AVR_ATmega644A__)
00186 #  include <avr/iom644.h>
00187 #elif defined (__AVR_ATmega644P__)
00188 #  include <avr/iom644p.h>
00189 #elif defined (__AVR_ATmega644PA__)
00190 #  include <avr/iom644pa.h>
00191 #elif defined (__AVR_ATmega645__) || defined (__AVR_ATmega645A__) || defined (__AVR_ATmega645P__)
00192 #  include <avr/iom645.h>
00193 #elif defined (__AVR_ATmega6450__) || defined (__AVR_ATmega6450A__) || defined (__AVR_ATmega6450P__)
00194 #  include <avr/iom6450.h>
00195 #elif defined (__AVR_ATmega649__) || defined (__AVR_ATmega649A__)
00196 #  include <avr/iom649.h>
00197 #elif defined (__AVR_ATmega6490__) || defined (__AVR_ATmega6490A__) || defined (__AVR_ATmega6490P__)
00198 #  include <avr/iom6490.h>
00199 #elif defined (__AVR_ATmega649P__)
00200 #  include <avr/iom649p.h>
00201 #elif defined (__AVR_ATmega64HVE__)
00202 #  include <avr/iom64hve.h>
00203 #elif defined (__AVR_ATmega103__)
00204 #  include <avr/iom103.h>
00205 #elif defined (__AVR_ATmega32__)
00206 #  include <avr/iom32.h>
00207 #elif defined (__AVR_ATmega323__)
00208 #  include <avr/iom323.h>
00209 #elif defined (__AVR_ATmega324P__) || defined (__AVR_ATmega324A__)
00210 #  include <avr/iom324.h>
00211 #elif defined (__AVR_ATmega324PA__)
00212 #  include <avr/iom324pa.h>
00213 #elif defined (__AVR_ATmega325__) || defined (__AVR_ATmega325A__)
00214 #  include <avr/iom325.h>
00215 #elif defined (__AVR_ATmega325P__)
00216 #  include <avr/iom325.h>
00217 #elif defined (__AVR_ATmega3250__) || defined (__AVR_ATmega3250A__)
00218 #  include <avr/iom3250.h>
00219 #elif defined (__AVR_ATmega3250P__)
00220 #  include <avr/iom3250.h>
00221 #elif defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
00222 #  include <avr/iom328p.h>
00223 #elif defined (__AVR_ATmega329__) || defined (__AVR_ATmega329A__)
00224 #  include <avr/iom329.h>
00225 #elif defined (__AVR_ATmega329P__) || defined (__AVR_ATmega329PA__)
00226 #  include <avr/iom329.h>
00227 #elif defined (__AVR_ATmega3290__) || defined (__AVR_ATmega3290A__)
00228 #  include <avr/iom3290.h>
00229 #elif defined (__AVR_ATmega3290P__)
00230 #  include <avr/iom3290.h>
00231 #elif defined (__AVR_ATmega32HVB__)
00232 #  include <avr/iom32hvb.h>
00233 #elif defined (__AVR_ATmega32HVBREVB__)
00234 #  include <avr/iom32hvbrevb.h>
00235 #elif defined (__AVR_ATmega406__)
00236 #  include <avr/iom406.h>
00237 #elif defined (__AVR_ATmega16__)
00238 #  include <avr/iom16.h>
00239 #elif defined (__AVR_ATmega16A__)
00240 #  include <avr/iom16a.h>
00241 #elif defined (__AVR_ATmega161__)
00242 #  include <avr/iom161.h>
00243 #elif defined (__AVR_ATmega162__)
00244 #  include <avr/iom162.h>
00245 #elif defined (__AVR_ATmega163__)
00246 #  include <avr/iom163.h>
00247 #elif defined (__AVR_ATmega164P__) || defined (__AVR_ATmega164A__)
00248 #  include <avr/iom164.h>
00249 #elif defined (__AVR_ATmega165__) || defined (__AVR_ATmega165A__)
00250 #  include <avr/iom165.h>
00251 #elif defined (__AVR_ATmega165P__)
00252 #  include <avr/iom165p.h>
00253 #elif defined (__AVR_ATmega168__) || defined (__AVR_ATmega168A__)
00254 #  include <avr/iom168.h>
00255 #elif defined (__AVR_ATmega168P__)
00256 #  include <avr/iom168p.h>
00257 #elif defined (__AVR_ATmega169__) || defined (__AVR_ATmega169A__)
00258 #  include <avr/iom169.h>
00259 #elif defined (__AVR_ATmega169P__)
00260 #  include <avr/iom169p.h>
00261 #elif defined (__AVR_ATmega169PA__)
00262 #  include <avr/iom169pa.h>
00263 #elif defined (__AVR_ATmega8HVA__)
00264 #  include <avr/iom8hva.h>
00265 #elif defined (__AVR_ATmega16HVA__)
00266 #  include <avr/iom16hva.h>
00267 #elif defined (__AVR_ATmega16HVA2__)
00268 #  include <avr/iom16hva2.h>
00269 #elif defined (__AVR_ATmega16HVB__)
00270 #  include <avr/iom16hvb.h>
00271 #elif defined (__AVR_ATmega16HVBREVB__)
00272 #  include <avr/iom16hvbrevb.h>
00273 #elif defined (__AVR_ATmega8__)
00274 #  include <avr/iom8.h>
00275 #elif defined (__AVR_ATmega48__) || defined (__AVR_ATmega48A__)
00276 #  include <avr/iom48.h>
00277 #elif defined (__AVR_ATmega48P__)
00278 #  include <avr/iom48p.h>
00279 #elif defined (__AVR_ATmega88__) || defined (__AVR_ATmega88A__)
00280 #  include <avr/iom88.h>
00281 #elif defined (__AVR_ATmega88P__)
00282 #  include <avr/iom88p.h>
00283 #elif defined (__AVR_ATmega88PA__)
00284 #  include <avr/iom88pa.h>
00285 #elif defined (__AVR_ATmega8515__)
00286 #  include <avr/iom8515.h>
00287 #elif defined (__AVR_ATmega8535__)
00288 #  include <avr/iom8535.h>
00289 #elif defined (__AVR_AT90S8535__)
00290 #  include <avr/io8535.h>
00291 #elif defined (__AVR_AT90C8534__)
00292 #  include <avr/io8534.h>
00293 #elif defined (__AVR_AT90S8515__)
00294 #  include <avr/io8515.h>
00295 #elif defined (__AVR_AT90S4434__)
00296 #  include <avr/io4434.h>
00297 #elif defined (__AVR_AT90S4433__)
00298 #  include <avr/io4433.h>
00299 #elif defined (__AVR_AT90S4414__)
00300 #  include <avr/io4414.h>
00301 #elif defined (__AVR_ATtiny22__)
00302 #  include <avr/iotn22.h>
00303 #elif defined (__AVR_ATtiny26__)
00304 #  include <avr/iotn26.h>
00305 #elif defined (__AVR_AT90S2343__)
00306 #  include <avr/io2343.h>
00307 #elif defined (__AVR_AT90S2333__)
00308 #  include <avr/io2333.h>
00309 #elif defined (__AVR_AT90S2323__)
00310 #  include <avr/io2323.h>
00311 #elif defined (__AVR_AT90S2313__)
00312 #  include <avr/io2313.h>
00313 #elif defined (__AVR_ATtiny4__)
00314 #  include <avr/iotn4.h>
00315 #elif defined (__AVR_ATtiny5__)
00316 #  include <avr/iotn5.h>
00317 #elif defined (__AVR_ATtiny9__)
00318 #  include <avr/iotn9.h>
00319 #elif defined (__AVR_ATtiny10__)
00320 #  include <avr/iotn10.h>
00321 #elif defined (__AVR_ATtiny20__)
00322 #  include <avr/iotn20.h>
00323 #elif defined (__AVR_ATtiny40__)
00324 #  include <avr/iotn40.h>
00325 #elif defined (__AVR_ATtiny2313__)
00326 #  include <avr/iotn2313.h>
00327 #elif defined (__AVR_ATtiny2313A__)
00328 #  include <avr/iotn2313a.h>
00329 #elif defined (__AVR_ATtiny13__)
00330 #  include <avr/iotn13.h>
00331 #elif defined (__AVR_ATtiny13A__)
00332 #  include <avr/iotn13a.h>
00333 #elif defined (__AVR_ATtiny25__)
00334 #  include <avr/iotn25.h>
00335 #elif defined (__AVR_ATtiny4313__)
00336 #  include <avr/iotn4313.h>
00337 #elif defined (__AVR_ATtiny45__)
00338 #  include <avr/iotn45.h>
00339 #elif defined (__AVR_ATtiny85__)
00340 #  include <avr/iotn85.h>
00341 #elif defined (__AVR_ATtiny24__)
00342 #  include <avr/iotn24.h>
00343 #elif defined (__AVR_ATtiny24A__)
00344 #  include <avr/iotn24a.h>
00345 #elif defined (__AVR_ATtiny44__)
00346 #  include <avr/iotn44.h>
00347 #elif defined (__AVR_ATtiny44A__)
00348 #  include <avr/iotn44a.h>
00349 #elif defined (__AVR_ATtiny84__)
00350 #  include <avr/iotn84.h>
00351 #elif defined (__AVR_ATtiny84A__)
00352 #  include <avr/iotn84a.h>
00353 #elif defined (__AVR_ATtiny261__)
00354 #  include <avr/iotn261.h>
00355 #elif defined (__AVR_ATtiny261A__)
00356 #  include <avr/iotn261a.h>
00357 #elif defined (__AVR_ATtiny461__)
00358 #  include <avr/iotn461.h>
00359 #elif defined (__AVR_ATtiny461A__)
00360 #  include <avr/iotn461a.h>
00361 #elif defined (__AVR_ATtiny861__)
00362 #  include <avr/iotn861.h>
00363 #elif defined (__AVR_ATtiny861A__)
00364 #  include <avr/iotn861a.h>
00365 #elif defined (__AVR_ATtiny43U__)
00366 #  include <avr/iotn43u.h>
00367 #elif defined (__AVR_ATtiny48__)
00368 #  include <avr/iotn48.h>
00369 #elif defined (__AVR_ATtiny88__)
00370 #  include <avr/iotn88.h>
00371 #elif defined (__AVR_ATtiny87__)
00372 #  include <avr/iotn87.h>
00373 #elif defined (__AVR_ATtiny167__)
00374 #  include <avr/iotn167.h>
00375 #elif defined (__AVR_AT90SCR100__)
00376 #  include <avr/io90scr100.h>
00377 #elif defined (__AVR_ATxmega16A4__)
00378 #  include <avr/iox16a4.h>
00379 #elif defined (__AVR_ATxmega16D4__)
00380 #  include <avr/iox16d4.h>
00381 #elif defined (__AVR_ATxmega32A4__)
00382 #  include <avr/iox32a4.h>
00383 #elif defined (__AVR_ATxmega32D4__)
00384 #  include <avr/iox32d4.h>
00385 #elif defined (__AVR_ATxmega64A1__)
00386 #  include <avr/iox64a1.h>
00387 #elif defined (__AVR_ATxmega64A1U__)
00388 #  include <avr/iox64a1u.h>
00389 #elif defined (__AVR_ATxmega64A3__)
00390 #  include <avr/iox64a3.h>
00391 #elif defined (__AVR_ATxmega64D3__)
00392 #  include <avr/iox64d3.h>
00393 #elif defined (__AVR_ATxmega128A1__)
00394 #  include <avr/iox128a1.h>
00395 #elif defined (__AVR_ATxmega128A1U__)
00396 #  include <avr/iox128a1u.h>
00397 #elif defined (__AVR_ATxmega128A3__)
00398 #  include <avr/iox128a3.h>
00399 #elif defined (__AVR_ATxmega128D3__)
00400 #  include <avr/iox128d3.h>
00401 #elif defined (__AVR_ATxmega192A3__)
00402 #  include <avr/iox192a3.h>
00403 #elif defined (__AVR_ATxmega192D3__)
00404 #  include <avr/iox192d3.h>
00405 #elif defined (__AVR_ATxmega256A3__)
00406 #  include <avr/iox256a3.h>
00407 #elif defined (__AVR_ATxmega256A3B__)
00408 #  include <avr/iox256a3b.h>
00409 #elif defined (__AVR_ATxmega256D3__)
00410 #  include <avr/iox256d3.h>
00411 #elif defined (__AVR_ATA6289__)
00412 #  include <avr/ioa6289.h>
00413 /* avr1: the following only supported for assembler programs */
00414 #elif defined (__AVR_ATtiny28__)
00415 #  include <avr/iotn28.h>
00416 #elif defined (__AVR_AT90S1200__)
00417 #  include <avr/io1200.h>
00418 #elif defined (__AVR_ATtiny15__)
00419 #  include <avr/iotn15.h>
00420 #elif defined (__AVR_ATtiny12__)
00421 #  include <avr/iotn12.h>
00422 #elif defined (__AVR_ATtiny11__)
00423 #  include <avr/iotn11.h>
00424 #elif defined (__AVR_M3000__)
00425 #  include <avr/iom3000.h>
00426 #else
00427 #  if !defined(__COMPILING_AVR_LIBC__)
00428 #    warning "device type not defined"
00429 #  endif
00430 #endif
00431 
00432 #include <avr/portpins.h>
00433 
00434 #include <avr/common.h>
00435 
00436 #include <avr/version.h>
00437 
00438 /* Include fuse.h after individual IO header files. */
00439 #include <avr/fuse.h>
00440 
00441 /* Include lock.h after individual IO header files. */
00442 #include <avr/lock.h>
00443 
00444 #endif /* _AVR_IO_H_ */