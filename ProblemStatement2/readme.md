# Problem Statement 2: nPM1100 Evaluation PCB

## Overview

This folder includes both the schematic (PDF) and PCB design (PDF) of the PCB based on the nPM1100 power management IC by Nordic Semiconductor.
Link - https://www.nordicsemi.com/Products/nPM1100/Get-started

The datasheet used for reference has been taken from the same website. 
Used nPM1100 Product Specification v1.5:
Link - https://docs.nordicsemi.com/bundle/ps_npm1100/page/keyfeatures_html5.html

## Design Specifications

- Output Voltage: 3.0V
	Ensured, since VBAT has been scaled down appropriately using the 150k and 560k ohm resistors as voltage dividers.
	This scaled output has also been sent out to measure the Battery Voltage using the MCU (Bonus Task)

- Charging Current: 200mA
	R_ICHG1 value has been set appropriately. 
	Note - The closest available value, 2.2k Ohm has been taken, charging current may vary accordingly

- Package: QFN 4x4mm (QFN50P400X400X90-25N)
	The footprint has been externally sourced from here - https://www.snapeda.com/parts/NPM1100-QDAB-R7/Nordic%20Semiconductor%20ASA/view-part/?ref=search&t=npm1100&ab_test_case=b
	And has been modified to suit the 4.0x4.0 package mentioned in section 8.2.2 of the datasheet.

- Symbol Design 
	The block diagram in section 3.1 of the datasheet has been used for reference.

- Circuit Design 
	Configuration 1 in the Reference Circuitry (Section 8.3.1 of the datasheet - QFN Schematic - has been used)

- PCB Size: 22.5mm x 20mm

- Connectors: 2.00mm pitch pin headers (1x2 and 1x4 variants)
	J1 - Input Battery 
	J2 - Measure battery voltage (scaled appropriately to 3v)
	J4 - Relevant IO pins extracted to be exposed to host MCU.

- Indicators: 3 LEDs for CHG (Charging - Red), POW (Power - Green), and ERR (Yellow)

## Design Constraints
- All components are SMD
- All 0603 size parts used
- Silkscreen includes header labels on alternating sides
- BOM includes LCSC and Mouser sourced MPNs with footprint compatibility

## Output Files
- 'Schematic.pdf' – schematic diagram
- 'pcb_design.pdf' – Fully routed PCB with silkscreens, copper, masks, etc. in different configurations along with the working area design screenshots and the 3D Views.
- 'BOM.csv' – Bill of Materials with MPNs, Footprints, and References

## Tools Used
- KiCad 7.0

## Component sourcing
- LCSC
- Mouser

## NOTES
- The PCB has been fully self designed, i.e., no reference has been used from anywhere to layout/route the PCB. 
- All routings/layouts/schematic designed have been self done, without any external reference. 
- Placement, naming, and silkscreen are optimized for readability and manufacture.
- Follows all constraints mentioned in the problem statement.
