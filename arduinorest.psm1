#-----Script Info---------------------------------------------------------------------------------------------
# Name:ArduinoREST.psm1
# Author: Einar Stenberg
# Date: 18.06.15
# Version: 2
# Job/Tasks: Send REST commands to control arduino
#--------------------------------------------------------------------------------------------------------------

#-----Changelog------------------------------------------------------------------------------------------------
#v1.  Script created ES
#v2.  Added Lightsoff 
#
#--------------------------------------------------------------------------------------------------------------




#-----Functions---------------------------------------------------------------------------------------------

Function Set-ArduinoLed{

<#
.SYNOPSIS
Set LED colours on arduino controlpanel
.DESCRIPTION
Sends information to REST interface of Arduino and sets LED colour

Part of ESPS by ES
.PARAMETER Server
IP or DNS name of Arduino
.PARAMETER LedNumber
ID number of LED to set
.PARAMETER RedValue
Set Red LED value (Higher is brighter)
.PARAMETER GreenValue
Set Green LED value (Higher is brighter)
.PARAMETER BlueValue
Set Blue LED value (Higher is brighter)
.PARAMETER SimpleColour
Set clolour to one of preset combined values
.EXAMPLE
Set-ArduinoLed -Server 10.0.0.45 -LedNumber 8 -RedValue 255 -GreenValue 255 -BlueValue 0
Sets LED number 8 on arduino with ip 10.0.0.45 to Yellow
.EXAMPLE
Set-ArduinoLed -Server 10.0.0.45 -LedNumber 8 -SimpleColour Yellow
Sets LED number 8 on arduino with ip 10.0.0.45 to Yellow
#>

Param(
[Parameter(Mandatory=$true)][string]$Server,
[Parameter(Mandatory=$true)][int]$LedNumber,
[ValidateRange(0,255)][int]$RedValue = 0,
[ValidateRange(0,255)][int]$GreenValue = 0,
[ValidateRange(0,255)][int]$BlueValue = 0,
[ValidateSet("Red","Green","Blue","Yellow","Orange","White","Black")][string]$SimpleColour
)

switch ($SimpleColour){
    "Red" {$RedValue = 255}
    "Green" {$GreenValue = 255}
    "Blue" {$BlueValue = 255}
    "Yellow" {$RedValue = 255; $GreenValue = 255}
    "Orange" {$RedValue = 255; $GreenValue = 69}
    "White" {$RedValue = 255; $GreenValue = 255; $BlueValue = 255}
    "Black" {$RedValue = 0; $GreenValue = 0; $BlueValue = 0}
}


Invoke-WebRequest -Method Get -Uri "http://$Server/SetLeds?params=$LedNumber,$RedValue,$GreenValue,$BlueValue,"


}

Function Toggle-ArduinoLed{

Param(
[Parameter(Mandatory=$true)][string]$Server,
[ValidateSet("On","Off","TOGGLE")][string]$Lights="TOGGLE"
)

if ($Lights -eq "TOGGLE"){$Lightsstatus="5"}
if ($Lights -eq "Off"){$Lightsstatus="1"}
if ($Lights -eq "On"){$Lightsstatus="0"}

Invoke-WebRequest -Method Get -Uri "http://$Server/LightsToggle?params=$Lightsstatus"
}