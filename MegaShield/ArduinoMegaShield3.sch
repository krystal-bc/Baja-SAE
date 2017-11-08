<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="8.4.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="frames" urn="urn:adsk.eagle:library:229">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="FRAME_A_L" urn="urn:adsk.eagle:symbol:13882/1" library_version="1">
<frame x1="0" y1="0" x2="279.4" y2="215.9" columns="6" rows="5" layer="94" border-bottom="no"/>
</symbol>
<symbol name="DOCFIELD" urn="urn:adsk.eagle:symbol:13864/1" library_version="1">
<wire x1="0" y1="0" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="87.63" y2="15.24" width="0.1016" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="71.12" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="0" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="87.63" y1="5.08" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="0" y1="15.24" x2="0" y2="22.86" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="22.86" x2="101.6" y2="15.24" width="0.1016" layer="94"/>
<text x="1.27" y="1.27" size="2.54" layer="94">Date:</text>
<text x="12.7" y="1.27" size="2.54" layer="94">&gt;LAST_DATE_TIME</text>
<text x="72.39" y="1.27" size="2.54" layer="94">Sheet:</text>
<text x="86.36" y="1.27" size="2.54" layer="94">&gt;SHEET</text>
<text x="88.9" y="11.43" size="2.54" layer="94">REV:</text>
<text x="1.27" y="19.05" size="2.54" layer="94">TITLE:</text>
<text x="1.27" y="11.43" size="2.54" layer="94">Document Number:</text>
<text x="17.78" y="19.05" size="2.54" layer="94">&gt;DRAWING_NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="FRAME_A_L" urn="urn:adsk.eagle:component:13939/1" prefix="FRAME" uservalue="yes" library_version="1">
<description>&lt;b&gt;FRAME&lt;/b&gt; A Size , 8 1/2 x 11 INCH, Landscape&lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="FRAME_A_L" x="0" y="0" addlevel="always"/>
<gate name="G$2" symbol="DOCFIELD" x="172.72" y="0" addlevel="always"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ArduinoMegaShield2">
<packages>
<package name="8PINHEADER2.54MM">
<wire x1="-10.16" y1="-1.27" x2="10.16" y2="-1.27" width="0.127" layer="21"/>
<wire x1="10.16" y1="-1.27" x2="10.16" y2="1.27" width="0.127" layer="21"/>
<wire x1="10.16" y1="1.27" x2="-10.16" y2="1.27" width="0.127" layer="21"/>
<wire x1="-10.16" y1="1.27" x2="-10.16" y2="-1.27" width="0.127" layer="21"/>
<pad name="P$1" x="-8.89" y="0" drill="1.1" diameter="2"/>
<pad name="P$2" x="-6.35" y="0" drill="1.1" diameter="2"/>
<pad name="P$3" x="-3.81" y="0" drill="1.1" diameter="2"/>
<pad name="P$4" x="-1.27" y="0" drill="1.1" diameter="2"/>
<pad name="P$5" x="1.27" y="0" drill="1.1" diameter="2"/>
<pad name="P$6" x="3.81" y="0" drill="1.1" diameter="2"/>
<pad name="P$7" x="6.35" y="0" drill="1.1" diameter="2"/>
<pad name="P$8" x="8.89" y="0" drill="1.1" diameter="2"/>
</package>
<package name="10PINHEADER2.54MM">
<wire x1="-12.7" y1="-1.27" x2="12.7" y2="-1.27" width="0.127" layer="21"/>
<wire x1="12.7" y1="-1.27" x2="12.7" y2="1.27" width="0.127" layer="21"/>
<wire x1="12.7" y1="1.27" x2="-12.7" y2="1.27" width="0.127" layer="21"/>
<wire x1="-12.7" y1="1.27" x2="-12.7" y2="-1.27" width="0.127" layer="21"/>
<pad name="P$1" x="1.27" y="0" drill="1.1" diameter="2"/>
<pad name="P$2" x="3.81" y="0" drill="1.1" diameter="2"/>
<pad name="P$3" x="6.35" y="0" drill="1.1" diameter="2"/>
<pad name="P$4" x="8.89" y="0" drill="1.1" diameter="2"/>
<pad name="P$5" x="11.43" y="0" drill="1.1" diameter="2"/>
<pad name="P$6" x="-1.27" y="0" drill="1.1" diameter="2"/>
<pad name="P$7" x="-3.81" y="0" drill="1.1" diameter="2"/>
<pad name="P$8" x="-6.35" y="0" drill="1.1" diameter="2"/>
<pad name="P$9" x="-8.89" y="0" drill="1.1" diameter="2"/>
<pad name="P$10" x="-11.43" y="0" drill="1.1" diameter="2"/>
</package>
<package name="18X2HEADER2.54MM">
<wire x1="-22.86" y1="-2.54" x2="22.86" y2="-2.54" width="0.127" layer="21"/>
<wire x1="22.86" y1="-2.54" x2="22.86" y2="2.54" width="0.127" layer="21"/>
<wire x1="22.86" y1="2.54" x2="-22.86" y2="2.54" width="0.127" layer="21"/>
<wire x1="-22.86" y1="2.54" x2="-22.86" y2="-2.54" width="0.127" layer="21"/>
<pad name="P$1" x="-21.59" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$2" x="-19.05" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$3" x="-16.51" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$4" x="-13.97" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$5" x="-11.43" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$6" x="-8.89" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$7" x="-6.35" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$8" x="-3.81" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$9" x="-1.27" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$10" x="1.27" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$11" x="3.81" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$12" x="6.35" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$13" x="8.89" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$14" x="11.43" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$15" x="13.97" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$16" x="16.51" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$17" x="19.05" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$18" x="21.59" y="1.27" drill="1.1" diameter="2"/>
<pad name="P$19" x="21.59" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$20" x="19.05" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$21" x="16.51" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$22" x="13.97" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$23" x="11.43" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$24" x="8.89" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$25" x="6.35" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$26" x="3.81" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$27" x="1.27" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$28" x="-1.27" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$29" x="-3.81" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$30" x="-6.35" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$31" x="-8.89" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$32" x="-11.43" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$33" x="-13.97" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$34" x="-16.51" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$35" x="-19.05" y="-1.27" drill="1.1" diameter="2"/>
<pad name="P$36" x="-21.59" y="-1.27" drill="1.1" diameter="2"/>
</package>
<package name="5PINHEADER2.54MM">
<wire x1="-6.35" y1="1.27" x2="-6.35" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-6.35" y1="-1.27" x2="6.35" y2="-1.27" width="0.127" layer="21"/>
<wire x1="6.35" y1="-1.27" x2="6.35" y2="1.27" width="0.127" layer="21"/>
<wire x1="6.35" y1="1.27" x2="-6.35" y2="1.27" width="0.127" layer="21"/>
<pad name="P$1" x="-5.08" y="0" drill="1.1" diameter="2"/>
<pad name="P$2" x="-2.54" y="0" drill="1.1" diameter="2"/>
<pad name="P$3" x="0" y="0" drill="1.1" diameter="2"/>
<pad name="GND" x="2.54" y="0" drill="1.1" diameter="2"/>
<pad name="5V" x="5.08" y="0" drill="1.1" diameter="2"/>
</package>
<package name="SDCARDMODULE">
<wire x1="-10.16" y1="-1.27" x2="10.16" y2="-1.27" width="0.127" layer="21"/>
<wire x1="10.16" y1="-1.27" x2="10.16" y2="1.27" width="0.127" layer="21"/>
<wire x1="10.16" y1="1.27" x2="-10.16" y2="1.27" width="0.127" layer="21"/>
<wire x1="-10.16" y1="1.27" x2="-10.16" y2="-1.27" width="0.127" layer="21"/>
<pad name="P$1" x="-8.89" y="0" drill="1.1" diameter="2"/>
<pad name="P$2" x="-6.35" y="0" drill="1.1" diameter="2"/>
<pad name="P$3" x="-3.81" y="0" drill="1.1" diameter="2"/>
<pad name="P$4" x="-1.27" y="0" drill="1.1" diameter="2"/>
<pad name="P$5" x="1.27" y="0" drill="1.1" diameter="2"/>
<pad name="GND" x="3.81" y="0" drill="1.1" diameter="2"/>
<pad name="P$7" x="6.35" y="0" drill="1.1" diameter="2"/>
<pad name="5V" x="8.89" y="0" drill="1.1" diameter="2"/>
</package>
<package name="SERVOS">
<pad name="P$1" x="0" y="0" drill="1.1" diameter="2"/>
<pad name="5V" x="2.54" y="0" drill="1.1" diameter="2"/>
<pad name="GND" x="5.08" y="0" drill="1.1" diameter="2"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="6.35" y2="-1.27" width="0.127" layer="21"/>
<wire x1="6.35" y1="-1.27" x2="6.35" y2="1.27" width="0.127" layer="21"/>
<wire x1="6.35" y1="1.27" x2="-1.27" y2="1.27" width="0.127" layer="21"/>
</package>
<package name="HALLEFFECTSENSORS">
<pad name="P$1" x="0" y="0" drill="1.1" diameter="2"/>
<pad name="P$2" x="2.54" y="0" drill="1.1" diameter="2"/>
<pad name="GND" x="5.08" y="0" drill="1.1" diameter="2"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="6.35" y2="-1.27" width="0.127" layer="21"/>
<wire x1="6.35" y1="-1.27" x2="6.35" y2="1.27" width="0.127" layer="21"/>
<wire x1="6.35" y1="1.27" x2="-1.27" y2="1.27" width="0.127" layer="21"/>
</package>
<package name="2PIN2.54MM">
<pad name="P$1" x="0" y="0" drill="1.1" diameter="2"/>
<pad name="GND" x="2.54" y="0" drill="1.1" diameter="2"/>
</package>
<package name="2PIN11MM">
<pad name="P$1" x="0" y="0" drill="1.1" diameter="2"/>
<pad name="5V" x="4.65" y="0" drill="1.1" diameter="2"/>
</package>
<package name="2PINTERMINAL3.5MM">
<pad name="5V" x="0" y="0" drill="1.1" diameter="2"/>
<pad name="GND" x="3.5" y="0" drill="1.1" diameter="2"/>
<wire x1="-1.75" y1="1.75" x2="-1.75" y2="-1.75" width="0.127" layer="21"/>
<wire x1="-1.75" y1="-1.75" x2="5.25" y2="-1.75" width="0.127" layer="21"/>
<wire x1="5.25" y1="-1.75" x2="5.25" y2="1.75" width="0.127" layer="21"/>
<wire x1="5.25" y1="1.75" x2="-1.75" y2="1.75" width="0.127" layer="21"/>
</package>
<package name="BUTTONS">
<pad name="P$1" x="0" y="0" drill="1.1" diameter="2"/>
<pad name="P$2" x="2.54" y="0" drill="1.1" diameter="2"/>
</package>
</packages>
<symbols>
<symbol name="8PINHEADER2.54MM">
<wire x1="-10.16" y1="-1.27" x2="10.16" y2="-1.27" width="0.254" layer="94"/>
<wire x1="10.16" y1="-1.27" x2="10.16" y2="1.27" width="0.254" layer="94"/>
<wire x1="10.16" y1="1.27" x2="-10.16" y2="1.27" width="0.254" layer="94"/>
<wire x1="-10.16" y1="1.27" x2="-10.16" y2="-1.27" width="0.254" layer="94"/>
<pin name="P$1" x="-8.89" y="0" length="middle" rot="R90"/>
<pin name="P$2" x="-6.35" y="0" length="middle" rot="R90"/>
<pin name="P$3" x="-3.81" y="0" length="middle" rot="R90"/>
<pin name="P$4" x="-1.27" y="0" length="middle" rot="R90"/>
<pin name="P$5" x="1.27" y="0" length="middle" rot="R90"/>
<pin name="P$6" x="3.81" y="0" length="middle" rot="R90"/>
<pin name="P$7" x="6.35" y="0" length="middle" rot="R90"/>
<pin name="P$8" x="8.89" y="0" length="middle" rot="R90"/>
</symbol>
<symbol name="10PINHEADER2.54MM">
<wire x1="-12.7" y1="-1.1" x2="12.7" y2="-1.1" width="0.254" layer="94"/>
<wire x1="12.7" y1="-1.1" x2="12.7" y2="1.1" width="0.254" layer="94"/>
<wire x1="12.7" y1="1.1" x2="-12.7" y2="1.1" width="0.254" layer="94"/>
<wire x1="-12.7" y1="1.1" x2="-12.7" y2="-1.1" width="0.254" layer="94"/>
<pin name="P$1" x="-1.27" y="0" length="middle" rot="R90"/>
<pin name="P$2" x="-3.81" y="0" length="middle" rot="R90"/>
<pin name="P$3" x="-6.35" y="0" length="middle" rot="R90"/>
<pin name="P$4" x="-8.89" y="0" length="middle" rot="R90"/>
<pin name="P$5" x="-11.43" y="0" length="middle" rot="R90"/>
<pin name="P$6" x="1.27" y="0" length="middle" rot="R90"/>
<pin name="P$7" x="3.81" y="0" length="middle" rot="R90"/>
<pin name="P$8" x="6.35" y="0" length="middle" rot="R90"/>
<pin name="P$9" x="8.89" y="0" length="middle" rot="R90"/>
<pin name="P$10" x="11.43" y="0" length="middle" rot="R90"/>
</symbol>
<symbol name="18X2HEADER2.54MM">
<wire x1="-22.86" y1="-2.54" x2="22.86" y2="-2.54" width="0.254" layer="94"/>
<wire x1="22.86" y1="-2.54" x2="22.86" y2="2.54" width="0.254" layer="94"/>
<wire x1="22.86" y1="2.54" x2="-22.86" y2="2.54" width="0.254" layer="94"/>
<wire x1="-22.86" y1="2.54" x2="-22.86" y2="-2.54" width="0.254" layer="94"/>
<pin name="P$1" x="-21.59" y="1.27" length="middle" rot="R90"/>
<pin name="P$2" x="-19.05" y="1.27" length="middle" rot="R90"/>
<pin name="P$3" x="-16.51" y="1.27" length="middle" rot="R90"/>
<pin name="P$4" x="-13.97" y="1.27" length="middle" rot="R90"/>
<pin name="P$5" x="-11.43" y="1.27" length="middle" rot="R90"/>
<pin name="P$6" x="-8.89" y="1.27" length="middle" rot="R90"/>
<pin name="P$7" x="-6.35" y="1.27" length="middle" rot="R90"/>
<pin name="P$8" x="-3.81" y="1.27" length="middle" rot="R90"/>
<pin name="P$9" x="-1.27" y="1.27" length="middle" rot="R90"/>
<pin name="P$10" x="1.27" y="1.27" length="middle" rot="R90"/>
<pin name="P$11" x="3.81" y="1.27" length="middle" rot="R90"/>
<pin name="P$12" x="6.35" y="1.27" length="middle" rot="R90"/>
<pin name="P$13" x="8.89" y="1.27" length="middle" rot="R90"/>
<pin name="P$14" x="11.43" y="1.27" length="middle" rot="R90"/>
<pin name="P$15" x="13.97" y="1.27" length="middle" rot="R90"/>
<pin name="P$16" x="16.51" y="1.27" length="middle" rot="R90"/>
<pin name="P$17" x="19.05" y="1.27" length="middle" rot="R90"/>
<pin name="P$18" x="21.59" y="1.27" length="middle" rot="R90"/>
<pin name="P$19" x="21.59" y="-1.27" length="middle" rot="R270"/>
<pin name="P$20" x="19.05" y="-1.27" length="middle" rot="R270"/>
<pin name="P$21" x="16.51" y="-1.27" length="middle" rot="R270"/>
<pin name="P$22" x="13.97" y="-1.27" length="middle" rot="R270"/>
<pin name="P$23" x="11.43" y="-1.27" length="middle" rot="R270"/>
<pin name="P$24" x="8.89" y="-1.27" length="middle" rot="R270"/>
<pin name="P$25" x="6.35" y="-1.27" length="middle" rot="R270"/>
<pin name="P$26" x="3.81" y="-1.27" length="middle" rot="R270"/>
<pin name="P$27" x="1.27" y="-1.27" length="middle" rot="R270"/>
<pin name="P$28" x="-1.27" y="-1.27" length="middle" rot="R270"/>
<pin name="P$29" x="-3.81" y="-1.27" length="middle" rot="R270"/>
<pin name="P$30" x="-6.35" y="-1.27" length="middle" rot="R270"/>
<pin name="P$31" x="-8.89" y="-1.27" length="middle" rot="R270"/>
<pin name="P$32" x="-11.43" y="-1.27" length="middle" rot="R270"/>
<pin name="P$33" x="-13.97" y="-1.27" length="middle" rot="R270"/>
<pin name="P$34" x="-16.51" y="-1.27" length="middle" rot="R270"/>
<pin name="P$35" x="-19.05" y="-1.27" length="middle" rot="R270"/>
<pin name="P$36" x="-21.59" y="-1.27" length="middle" rot="R270"/>
</symbol>
<symbol name="5PINHEADER2.54MM">
<pin name="P$1" x="-5.08" y="0" length="middle" rot="R90"/>
<pin name="P$2" x="-2.54" y="0" length="middle" rot="R90"/>
<pin name="P$3" x="0" y="0" length="middle" rot="R90"/>
<pin name="GND" x="2.54" y="0" length="middle" rot="R90"/>
<pin name="5V" x="5.08" y="0" length="middle" rot="R90"/>
<wire x1="-6.35" y1="1.27" x2="-6.35" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-6.35" y1="-1.27" x2="6.35" y2="-1.27" width="0.254" layer="94"/>
<wire x1="6.35" y1="-1.27" x2="6.35" y2="1.27" width="0.254" layer="94"/>
<wire x1="6.35" y1="1.27" x2="-6.35" y2="1.27" width="0.254" layer="94"/>
</symbol>
<symbol name="SDCARDMODULE">
<wire x1="-10.16" y1="-1.27" x2="10.16" y2="-1.27" width="0.254" layer="94"/>
<wire x1="10.16" y1="-1.27" x2="10.16" y2="1.27" width="0.254" layer="94"/>
<wire x1="10.16" y1="1.27" x2="-10.16" y2="1.27" width="0.254" layer="94"/>
<wire x1="-10.16" y1="1.27" x2="-10.16" y2="-1.27" width="0.254" layer="94"/>
<pin name="P$1" x="-8.89" y="0" length="middle" rot="R90"/>
<pin name="P$2" x="-6.35" y="0" length="middle" rot="R90"/>
<pin name="P$3" x="-3.81" y="0" length="middle" rot="R90"/>
<pin name="P$4" x="-1.27" y="0" length="middle" rot="R90"/>
<pin name="P$5" x="1.27" y="0" length="middle" rot="R90"/>
<pin name="GND" x="3.81" y="0" length="middle" rot="R90"/>
<pin name="P$7" x="6.35" y="0" length="middle" rot="R90"/>
<pin name="5V" x="8.89" y="0" length="middle" rot="R90"/>
</symbol>
<symbol name="SERVOS">
<pin name="P$1" x="0" y="0" length="middle" rot="R90"/>
<pin name="5V" x="2.54" y="0" length="middle" rot="R90"/>
<pin name="GND" x="5.08" y="0" length="middle" rot="R90"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-1.27" x2="6.35" y2="-1.27" width="0.254" layer="94"/>
<wire x1="6.35" y1="-1.27" x2="6.35" y2="1.27" width="0.254" layer="94"/>
<wire x1="6.35" y1="1.27" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
</symbol>
<symbol name="HALLEFFECTSENSORS">
<pin name="P$1" x="0" y="0" length="middle" rot="R90"/>
<pin name="P$2" x="2.54" y="0" length="middle" rot="R90"/>
<pin name="GND" x="5.08" y="0" length="middle" rot="R90"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-1.27" x2="6.35" y2="-1.27" width="0.254" layer="94"/>
<wire x1="6.35" y1="-1.27" x2="6.35" y2="1.27" width="0.254" layer="94"/>
<wire x1="6.35" y1="1.27" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
</symbol>
<symbol name="2PIN2.54MM">
<pin name="P$1" x="0" y="0" length="middle" rot="R90"/>
<pin name="GND" x="2.54" y="0" length="middle" rot="R90"/>
</symbol>
<symbol name="RESISTOR">
<pin name="P$1" x="0" y="0" length="middle" rot="R90"/>
<pin name="5V" x="5.92" y="0" length="middle" rot="R90"/>
</symbol>
<symbol name="2PINTERMINAL3.5MM">
<pin name="5V" x="0" y="0" length="middle" rot="R90"/>
<pin name="GND" x="3.5" y="0" length="middle" rot="R90"/>
<wire x1="-1.75" y1="1.75" x2="-1.75" y2="-1.75" width="0.254" layer="94"/>
<wire x1="-1.75" y1="-1.75" x2="5.25" y2="-1.75" width="0.254" layer="94"/>
<wire x1="5.25" y1="-1.75" x2="5.25" y2="1.75" width="0.254" layer="94"/>
<wire x1="5.25" y1="1.75" x2="-1.75" y2="1.75" width="0.254" layer="94"/>
</symbol>
<symbol name="BUTTONS">
<pin name="P$1" x="0" y="0" length="middle" rot="R90"/>
<pin name="P$2" x="2.54" y="0" length="middle" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="8PINHEADER2.54MM">
<gates>
<gate name="G$1" symbol="8PINHEADER2.54MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="8PINHEADER2.54MM">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
<connect gate="G$1" pin="P$3" pad="P$3"/>
<connect gate="G$1" pin="P$4" pad="P$4"/>
<connect gate="G$1" pin="P$5" pad="P$5"/>
<connect gate="G$1" pin="P$6" pad="P$6"/>
<connect gate="G$1" pin="P$7" pad="P$7"/>
<connect gate="G$1" pin="P$8" pad="P$8"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="10PINHEADER2.54MM">
<gates>
<gate name="G$1" symbol="10PINHEADER2.54MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="10PINHEADER2.54MM">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$10" pad="P$10"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
<connect gate="G$1" pin="P$3" pad="P$3"/>
<connect gate="G$1" pin="P$4" pad="P$4"/>
<connect gate="G$1" pin="P$5" pad="P$5"/>
<connect gate="G$1" pin="P$6" pad="P$6"/>
<connect gate="G$1" pin="P$7" pad="P$7"/>
<connect gate="G$1" pin="P$8" pad="P$8"/>
<connect gate="G$1" pin="P$9" pad="P$9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="18X2HEADER2.54MM">
<gates>
<gate name="G$1" symbol="18X2HEADER2.54MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="18X2HEADER2.54MM">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$10" pad="P$10"/>
<connect gate="G$1" pin="P$11" pad="P$11"/>
<connect gate="G$1" pin="P$12" pad="P$12"/>
<connect gate="G$1" pin="P$13" pad="P$13"/>
<connect gate="G$1" pin="P$14" pad="P$14"/>
<connect gate="G$1" pin="P$15" pad="P$15"/>
<connect gate="G$1" pin="P$16" pad="P$16"/>
<connect gate="G$1" pin="P$17" pad="P$17"/>
<connect gate="G$1" pin="P$18" pad="P$18"/>
<connect gate="G$1" pin="P$19" pad="P$19"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
<connect gate="G$1" pin="P$20" pad="P$20"/>
<connect gate="G$1" pin="P$21" pad="P$21"/>
<connect gate="G$1" pin="P$22" pad="P$22"/>
<connect gate="G$1" pin="P$23" pad="P$23"/>
<connect gate="G$1" pin="P$24" pad="P$24"/>
<connect gate="G$1" pin="P$25" pad="P$25"/>
<connect gate="G$1" pin="P$26" pad="P$26"/>
<connect gate="G$1" pin="P$27" pad="P$27"/>
<connect gate="G$1" pin="P$28" pad="P$28"/>
<connect gate="G$1" pin="P$29" pad="P$29"/>
<connect gate="G$1" pin="P$3" pad="P$3"/>
<connect gate="G$1" pin="P$30" pad="P$30"/>
<connect gate="G$1" pin="P$31" pad="P$31"/>
<connect gate="G$1" pin="P$32" pad="P$32"/>
<connect gate="G$1" pin="P$33" pad="P$33"/>
<connect gate="G$1" pin="P$34" pad="P$34"/>
<connect gate="G$1" pin="P$35" pad="P$35"/>
<connect gate="G$1" pin="P$36" pad="P$36"/>
<connect gate="G$1" pin="P$4" pad="P$4"/>
<connect gate="G$1" pin="P$5" pad="P$5"/>
<connect gate="G$1" pin="P$6" pad="P$6"/>
<connect gate="G$1" pin="P$7" pad="P$7"/>
<connect gate="G$1" pin="P$8" pad="P$8"/>
<connect gate="G$1" pin="P$9" pad="P$9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="5PINHEADER2.54MM">
<gates>
<gate name="G$1" symbol="5PINHEADER2.54MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="5PINHEADER2.54MM">
<connects>
<connect gate="G$1" pin="5V" pad="5V"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
<connect gate="G$1" pin="P$3" pad="P$3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SDCARDMODULE">
<gates>
<gate name="G$1" symbol="SDCARDMODULE" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SDCARDMODULE">
<connects>
<connect gate="G$1" pin="5V" pad="5V"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
<connect gate="G$1" pin="P$3" pad="P$3"/>
<connect gate="G$1" pin="P$4" pad="P$4"/>
<connect gate="G$1" pin="P$5" pad="P$5"/>
<connect gate="G$1" pin="P$7" pad="P$7"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SERVOS">
<gates>
<gate name="G$1" symbol="SERVOS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SERVOS">
<connects>
<connect gate="G$1" pin="5V" pad="5V"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="P$1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="HALLEFFECTSENSORS">
<gates>
<gate name="G$1" symbol="HALLEFFECTSENSORS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="HALLEFFECTSENSORS">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="2PIN2.54MM">
<gates>
<gate name="G$1" symbol="2PIN2.54MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2PIN2.54MM">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="P$1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="2PIN11MM">
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2PIN11MM">
<connects>
<connect gate="G$1" pin="5V" pad="5V"/>
<connect gate="G$1" pin="P$1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="2PINTERMINAL3.5MM">
<gates>
<gate name="G$1" symbol="2PINTERMINAL3.5MM" x="0" y="0"/>
</gates>
<devices>
<device name="" package="2PINTERMINAL3.5MM">
<connects>
<connect gate="G$1" pin="5V" pad="5V"/>
<connect gate="G$1" pin="GND" pad="GND"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BUTTONS">
<gates>
<gate name="G$1" symbol="BUTTONS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BUTTONS">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="FRAME1" library="frames" library_urn="urn:adsk.eagle:library:229" deviceset="FRAME_A_L" device=""/>
<part name="U$1" library="ArduinoMegaShield2" deviceset="8PINHEADER2.54MM" device=""/>
<part name="U$2" library="ArduinoMegaShield2" deviceset="8PINHEADER2.54MM" device=""/>
<part name="U$3" library="ArduinoMegaShield2" deviceset="8PINHEADER2.54MM" device=""/>
<part name="U$4" library="ArduinoMegaShield2" deviceset="8PINHEADER2.54MM" device=""/>
<part name="U$5" library="ArduinoMegaShield2" deviceset="8PINHEADER2.54MM" device=""/>
<part name="U$6" library="ArduinoMegaShield2" deviceset="10PINHEADER2.54MM" device=""/>
<part name="U$7" library="ArduinoMegaShield2" deviceset="18X2HEADER2.54MM" device=""/>
<part name="U$8" library="ArduinoMegaShield2" deviceset="5PINHEADER2.54MM" device=""/>
<part name="U$10" library="ArduinoMegaShield2" deviceset="SDCARDMODULE" device=""/>
<part name="U$9" library="ArduinoMegaShield2" deviceset="SERVOS" device=""/>
<part name="U$11" library="ArduinoMegaShield2" deviceset="SERVOS" device=""/>
<part name="U$12" library="ArduinoMegaShield2" deviceset="HALLEFFECTSENSORS" device=""/>
<part name="U$13" library="ArduinoMegaShield2" deviceset="HALLEFFECTSENSORS" device=""/>
<part name="U$14" library="ArduinoMegaShield2" deviceset="2PIN2.54MM" device=""/>
<part name="U$15" library="ArduinoMegaShield2" deviceset="2PIN2.54MM" device=""/>
<part name="U$17" library="ArduinoMegaShield2" deviceset="2PIN2.54MM" device=""/>
<part name="U$18" library="ArduinoMegaShield2" deviceset="2PIN2.54MM" device=""/>
<part name="U$19" library="ArduinoMegaShield2" deviceset="2PIN2.54MM" device=""/>
<part name="U$20" library="ArduinoMegaShield2" deviceset="2PIN11MM" device=""/>
<part name="U$21" library="ArduinoMegaShield2" deviceset="2PIN11MM" device=""/>
<part name="U$23" library="ArduinoMegaShield2" deviceset="2PINTERMINAL3.5MM" device=""/>
<part name="U$22" library="ArduinoMegaShield2" deviceset="BUTTONS" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="FRAME1" gate="G$1" x="0" y="0"/>
<instance part="FRAME1" gate="G$2" x="172.72" y="0"/>
<instance part="U$1" gate="G$1" x="121.92" y="66.04"/>
<instance part="U$2" gate="G$1" x="93.98" y="66.04"/>
<instance part="U$3" gate="G$1" x="93.98" y="129.54" rot="R180"/>
<instance part="U$4" gate="G$1" x="121.92" y="129.54" rot="R180"/>
<instance part="U$5" gate="G$1" x="152.4" y="129.54" rot="R180"/>
<instance part="U$6" gate="G$1" x="152.4" y="66.04"/>
<instance part="U$7" gate="G$1" x="66.04" y="99.06" rot="R90"/>
<instance part="U$8" gate="G$1" x="17.78" y="116.84" rot="R270"/>
<instance part="U$10" gate="G$1" x="40.64" y="88.9" rot="R90"/>
<instance part="U$9" gate="G$1" x="20.32" y="63.5"/>
<instance part="U$11" gate="G$1" x="33.02" y="63.5"/>
<instance part="U$12" gate="G$1" x="30.48" y="134.62" rot="R180"/>
<instance part="U$13" gate="G$1" x="40.64" y="134.62" rot="R180"/>
<instance part="U$14" gate="G$1" x="45.72" y="63.5"/>
<instance part="U$15" gate="G$1" x="50.8" y="63.5"/>
<instance part="U$17" gate="G$1" x="60.96" y="63.5"/>
<instance part="U$18" gate="G$1" x="66.04" y="63.5"/>
<instance part="U$19" gate="G$1" x="71.12" y="63.5"/>
<instance part="U$20" gate="G$1" x="121.92" y="104.14"/>
<instance part="U$21" gate="G$1" x="121.92" y="88.9"/>
<instance part="U$23" gate="G$1" x="53.34" y="134.62" rot="R180"/>
<instance part="U$22" gate="G$1" x="20.32" y="134.62" rot="R180"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$4" class="0">
<segment>
<pinref part="U$22" gate="G$1" pin="P$1"/>
<wire x1="20.32" y1="134.62" x2="20.32" y2="137.16" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P$7"/>
<wire x1="20.32" y1="137.16" x2="115.57" y2="137.16" width="0.1524" layer="91"/>
<wire x1="115.57" y1="137.16" x2="115.57" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="U$22" gate="G$1" pin="P$2"/>
<wire x1="17.78" y1="134.62" x2="17.78" y2="139.7" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P$6"/>
<wire x1="17.78" y1="139.7" x2="118.11" y2="139.7" width="0.1524" layer="91"/>
<wire x1="118.11" y1="139.7" x2="118.11" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="U$8" gate="G$1" pin="P$1"/>
<wire x1="17.78" y1="121.92" x2="40.64" y2="121.92" width="0.1524" layer="91"/>
<wire x1="40.64" y1="121.92" x2="40.64" y2="124.46" width="0.1524" layer="91"/>
<wire x1="40.64" y1="124.46" x2="55.88" y2="124.46" width="0.1524" layer="91"/>
<wire x1="55.88" y1="124.46" x2="55.88" y2="127" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P$2"/>
<wire x1="55.88" y1="127" x2="87.63" y2="127" width="0.1524" layer="91"/>
<wire x1="87.63" y1="127" x2="87.63" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="U$8" gate="G$1" pin="P$2"/>
<wire x1="17.78" y1="119.38" x2="43.18" y2="119.38" width="0.1524" layer="91"/>
<wire x1="43.18" y1="119.38" x2="43.18" y2="121.92" width="0.1524" layer="91"/>
<wire x1="43.18" y1="121.92" x2="58.42" y2="121.92" width="0.1524" layer="91"/>
<wire x1="58.42" y1="121.92" x2="58.42" y2="124.46" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P$1"/>
<wire x1="58.42" y1="124.46" x2="85.09" y2="124.46" width="0.1524" layer="91"/>
<wire x1="85.09" y1="124.46" x2="85.09" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="U$8" gate="G$1" pin="P$3"/>
<wire x1="17.78" y1="116.84" x2="12.7" y2="116.84" width="0.1524" layer="91"/>
<wire x1="12.7" y1="116.84" x2="12.7" y2="48.26" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P$3"/>
<wire x1="12.7" y1="48.26" x2="118.11" y2="48.26" width="0.1524" layer="91"/>
<wire x1="118.11" y1="48.26" x2="118.11" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<wire x1="40.64" y1="142.24" x2="134.62" y2="142.24" width="0.1524" layer="91"/>
<wire x1="134.62" y1="142.24" x2="134.62" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$20" gate="G$1" pin="P$1"/>
<wire x1="134.62" y1="116.84" x2="121.92" y2="116.84" width="0.1524" layer="91"/>
<wire x1="121.92" y1="116.84" x2="121.92" y2="104.14" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<wire x1="30.48" y1="147.32" x2="139.7" y2="147.32" width="0.1524" layer="91"/>
<wire x1="139.7" y1="147.32" x2="139.7" y2="101.6" width="0.1524" layer="91"/>
<pinref part="U$21" gate="G$1" pin="P$1"/>
<wire x1="139.7" y1="101.6" x2="121.92" y2="101.6" width="0.1524" layer="91"/>
<wire x1="121.92" y1="101.6" x2="121.92" y2="88.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="TOP" class="0">
<segment>
<wire x1="27.94" y1="149.86" x2="142.24" y2="149.86" width="0.1524" layer="91"/>
<wire x1="142.24" y1="149.86" x2="142.24" y2="99.06" width="0.1524" layer="91"/>
<pinref part="U$21" gate="G$1" pin="5V"/>
<wire x1="142.24" y1="99.06" x2="132.92" y2="99.06" width="0.1524" layer="91"/>
<wire x1="132.92" y1="99.06" x2="127.84" y2="88.9" width="0.1524" layer="91"/>
<wire x1="127.84" y1="88.9" x2="170.18" y2="88.9" width="0.1524" layer="91"/>
<wire x1="170.18" y1="88.9" x2="170.18" y2="154.94" width="0.1524" layer="91"/>
<junction x="127.84" y="88.9"/>
<wire x1="38.1" y1="144.78" x2="137.16" y2="144.78" width="0.1524" layer="91"/>
<wire x1="137.16" y1="144.78" x2="137.16" y2="109.22" width="0.1524" layer="91"/>
<pinref part="U$20" gate="G$1" pin="5V"/>
<wire x1="137.16" y1="109.22" x2="132.92" y2="109.22" width="0.1524" layer="91"/>
<wire x1="132.92" y1="109.22" x2="127.84" y2="104.14" width="0.1524" layer="91"/>
<wire x1="127.84" y1="104.14" x2="172.72" y2="104.14" width="0.1524" layer="91"/>
<wire x1="172.72" y1="104.14" x2="172.72" y2="157.48" width="0.1524" layer="91"/>
<junction x="127.84" y="104.14"/>
<wire x1="10.16" y1="97.79" x2="10.16" y2="139.7" width="0.1524" layer="91"/>
<pinref part="U$23" gate="G$1" pin="5V"/>
<wire x1="10.16" y1="139.7" x2="10.16" y2="165.1" width="0.1524" layer="91"/>
<wire x1="10.16" y1="165.1" x2="53.34" y2="165.1" width="0.1524" layer="91"/>
<wire x1="53.34" y1="165.1" x2="53.34" y2="157.48" width="0.1524" layer="91"/>
<pinref part="U$10" gate="G$1" pin="5V"/>
<wire x1="53.34" y1="157.48" x2="53.34" y2="154.94" width="0.1524" layer="91"/>
<wire x1="53.34" y1="154.94" x2="53.34" y2="134.62" width="0.1524" layer="91"/>
<wire x1="40.64" y1="97.79" x2="10.16" y2="97.79" width="0.1524" layer="91"/>
<wire x1="35.56" y1="58.42" x2="7.62" y2="58.42" width="0.1524" layer="91"/>
<wire x1="7.62" y1="58.42" x2="7.62" y2="139.7" width="0.1524" layer="91"/>
<wire x1="7.62" y1="139.7" x2="10.16" y2="139.7" width="0.1524" layer="91"/>
<junction x="10.16" y="139.7"/>
<wire x1="172.72" y1="157.48" x2="53.34" y2="157.48" width="0.1524" layer="91"/>
<junction x="53.34" y="157.48"/>
<wire x1="170.18" y1="154.94" x2="53.34" y2="154.94" width="0.1524" layer="91"/>
<junction x="53.34" y="154.94"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="U$10" gate="G$1" pin="P$5"/>
<wire x1="40.64" y1="90.17" x2="53.34" y2="90.17" width="0.1524" layer="91"/>
<wire x1="53.34" y1="90.17" x2="53.34" y2="76.2" width="0.1524" layer="91"/>
<wire x1="53.34" y1="76.2" x2="76.2" y2="76.2" width="0.1524" layer="91"/>
<wire x1="76.2" y1="76.2" x2="76.2" y2="119.38" width="0.1524" layer="91"/>
<pinref part="U$7" gate="G$1" pin="P$20"/>
<wire x1="76.2" y1="119.38" x2="67.31" y2="119.38" width="0.1524" layer="91"/>
<wire x1="67.31" y1="119.38" x2="67.31" y2="118.11" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="U$10" gate="G$1" pin="P$4"/>
<wire x1="40.64" y1="87.63" x2="50.8" y2="87.63" width="0.1524" layer="91"/>
<wire x1="50.8" y1="87.63" x2="50.8" y2="73.66" width="0.1524" layer="91"/>
<wire x1="50.8" y1="73.66" x2="78.74" y2="73.66" width="0.1524" layer="91"/>
<wire x1="78.74" y1="73.66" x2="78.74" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$7" gate="G$1" pin="P$21"/>
<wire x1="78.74" y1="116.84" x2="67.31" y2="116.84" width="0.1524" layer="91"/>
<wire x1="67.31" y1="116.84" x2="67.31" y2="115.57" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U$10" gate="G$1" pin="P$3"/>
<wire x1="40.64" y1="85.09" x2="55.88" y2="85.09" width="0.1524" layer="91"/>
<wire x1="55.88" y1="85.09" x2="55.88" y2="114.3" width="0.1524" layer="91"/>
<pinref part="U$7" gate="G$1" pin="P$16"/>
<wire x1="55.88" y1="114.3" x2="64.77" y2="114.3" width="0.1524" layer="91"/>
<wire x1="64.77" y1="114.3" x2="64.77" y2="115.57" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="U$10" gate="G$1" pin="P$2"/>
<wire x1="40.64" y1="82.55" x2="48.26" y2="82.55" width="0.1524" layer="91"/>
<wire x1="48.26" y1="82.55" x2="48.26" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$7" gate="G$1" pin="P$17"/>
<wire x1="48.26" y1="116.84" x2="64.77" y2="116.84" width="0.1524" layer="91"/>
<wire x1="64.77" y1="116.84" x2="64.77" y2="118.11" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="U$10" gate="G$1" pin="P$1"/>
<wire x1="40.64" y1="80.01" x2="53.34" y2="80.01" width="0.1524" layer="91"/>
<wire x1="53.34" y1="80.01" x2="53.34" y2="96.52" width="0.1524" layer="91"/>
<pinref part="U$7" gate="G$1" pin="P$9"/>
<wire x1="53.34" y1="96.52" x2="64.77" y2="96.52" width="0.1524" layer="91"/>
<wire x1="64.77" y1="96.52" x2="64.77" y2="97.79" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<wire x1="20.32" y1="50.8" x2="109.22" y2="50.8" width="0.1524" layer="91"/>
<wire x1="109.22" y1="50.8" x2="109.22" y2="109.22" width="0.1524" layer="91"/>
<pinref part="U$7" gate="G$1" pin="P$23"/>
<wire x1="109.22" y1="109.22" x2="67.31" y2="109.22" width="0.1524" layer="91"/>
<wire x1="67.31" y1="109.22" x2="67.31" y2="110.49" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<wire x1="33.02" y1="53.34" x2="106.68" y2="53.34" width="0.1524" layer="91"/>
<wire x1="106.68" y1="53.34" x2="106.68" y2="106.68" width="0.1524" layer="91"/>
<wire x1="106.68" y1="106.68" x2="67.31" y2="106.68" width="0.1524" layer="91"/>
<pinref part="U$7" gate="G$1" pin="P$24"/>
<wire x1="67.31" y1="106.68" x2="67.31" y2="107.95" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="U$14" gate="G$1" pin="P$1"/>
<wire x1="45.72" y1="63.5" x2="45.72" y2="55.88" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P$2"/>
<wire x1="45.72" y1="55.88" x2="115.57" y2="55.88" width="0.1524" layer="91"/>
<wire x1="115.57" y1="55.88" x2="115.57" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="U$15" gate="G$1" pin="P$1"/>
<wire x1="50.8" y1="63.5" x2="50.8" y2="58.42" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P$1"/>
<wire x1="50.8" y1="58.42" x2="113.03" y2="58.42" width="0.1524" layer="91"/>
<wire x1="113.03" y1="58.42" x2="113.03" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="U$17" gate="G$1" pin="P$1"/>
<wire x1="60.96" y1="63.5" x2="60.96" y2="20.32" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P$1"/>
<wire x1="60.96" y1="20.32" x2="151.13" y2="20.32" width="0.1524" layer="91"/>
<wire x1="151.13" y1="20.32" x2="151.13" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="U$18" gate="G$1" pin="P$1"/>
<wire x1="66.04" y1="63.5" x2="66.04" y2="22.86" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P$2"/>
<wire x1="66.04" y1="22.86" x2="148.59" y2="22.86" width="0.1524" layer="91"/>
<wire x1="148.59" y1="22.86" x2="148.59" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="U$19" gate="G$1" pin="P$1"/>
<wire x1="71.12" y1="63.5" x2="71.12" y2="25.4" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P$3"/>
<wire x1="71.12" y1="25.4" x2="146.05" y2="25.4" width="0.1524" layer="91"/>
<wire x1="146.05" y1="25.4" x2="146.05" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="U$23" gate="G$1" pin="GND"/>
<wire x1="33.02" y1="127" x2="45.72" y2="127" width="0.1524" layer="91"/>
<wire x1="45.72" y1="127" x2="49.84" y2="127" width="0.1524" layer="91"/>
<wire x1="49.84" y1="127" x2="49.84" y2="134.62" width="0.1524" layer="91"/>
<wire x1="25.4" y1="127" x2="33.02" y2="127" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="GND"/>
<wire x1="17.78" y1="114.3" x2="33.02" y2="114.3" width="0.1524" layer="91"/>
<wire x1="33.02" y1="114.3" x2="33.02" y2="127" width="0.1524" layer="91"/>
<junction x="33.02" y="127"/>
<pinref part="U$10" gate="G$1" pin="GND"/>
<wire x1="40.64" y1="92.71" x2="45.72" y2="92.71" width="0.1524" layer="91"/>
<wire x1="45.72" y1="92.71" x2="45.72" y2="127" width="0.1524" layer="91"/>
<junction x="45.72" y="127"/>
<wire x1="25.4" y1="76.2" x2="25.4" y2="127" width="0.1524" layer="91"/>
<wire x1="38.1" y1="73.66" x2="38.1" y2="76.2" width="0.1524" layer="91"/>
<wire x1="38.1" y1="76.2" x2="25.4" y2="76.2" width="0.1524" layer="91"/>
<pinref part="U$14" gate="G$1" pin="GND"/>
<wire x1="48.26" y1="63.5" x2="48.26" y2="71.12" width="0.1524" layer="91"/>
<wire x1="48.26" y1="71.12" x2="48.26" y2="73.66" width="0.1524" layer="91"/>
<wire x1="48.26" y1="73.66" x2="38.1" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$15" gate="G$1" pin="GND"/>
<wire x1="53.34" y1="63.5" x2="53.34" y2="71.12" width="0.1524" layer="91"/>
<wire x1="53.34" y1="71.12" x2="48.26" y2="71.12" width="0.1524" layer="91"/>
<junction x="48.26" y="71.12"/>
<junction x="53.34" y="71.12"/>
<pinref part="U$17" gate="G$1" pin="GND"/>
<wire x1="63.5" y1="63.5" x2="63.5" y2="71.12" width="0.1524" layer="91"/>
<wire x1="63.5" y1="71.12" x2="53.34" y2="71.12" width="0.1524" layer="91"/>
<pinref part="U$18" gate="G$1" pin="GND"/>
<wire x1="68.58" y1="63.5" x2="68.58" y2="71.12" width="0.1524" layer="91"/>
<wire x1="68.58" y1="71.12" x2="63.5" y2="71.12" width="0.1524" layer="91"/>
<junction x="63.5" y="71.12"/>
<pinref part="U$19" gate="G$1" pin="GND"/>
<wire x1="73.66" y1="63.5" x2="73.66" y2="71.12" width="0.1524" layer="91"/>
<wire x1="73.66" y1="71.12" x2="68.58" y2="71.12" width="0.1524" layer="91"/>
<junction x="68.58" y="71.12"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
