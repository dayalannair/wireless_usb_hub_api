====================
Wireless USB Hub API
====================


.. image:: https://img.shields.io/pypi/v/wireless_usb_hub_api.svg
        :target: https://pypi.python.org/pypi/wireless_usb_hub_api

.. image:: https://img.shields.io/travis/dayalannair/wireless_usb_hub_api.svg
        :target: https://travis-ci.com/dayalannair/wireless_usb_hub_api

.. image:: https://readthedocs.org/projects/wireless-usb-hub-api/badge/?version=latest
        :target: https://wireless-usb-hub-api.readthedocs.io/en/latest/?badge=latest
        :alt: Documentation Status




API for using Pi as a wireless USB hub.


* Free software: MIT license
* Documentation: https://wireless-usb-hub-api.readthedocs.io.


Features
--------
This API allows the user to send/receive data using a CC2500 tranceiver to/from a local USB device.

Configuration file:

-data rate: 500kbaud

-Mod.: MSK

-RX BW: 812 kHz

-Optimised for sensitivity

Includes a configuration file for mounting a USB on a Raspberry Pi.

Makes use of the spidev library for SPI communication.

PIN connections for Raspberry Pi and Quasar module:

PI  | Quasar
---------------

13  ---> 7 GDO0  

15  ---> 5 GDO1

17  ---> 1 VCC 

19  ---> 2 SI

21  ---> 4 SO 

23  ---> 3 SCLK

25  ---> 6 GND

24  ---> 8 CSn


Credits
-------

This package was created with Cookiecutter_ and the `audreyr/cookiecutter-pypackage`_ project template.

.. _Cookiecutter: https://github.com/audreyr/cookiecutter
.. _`audreyr/cookiecutter-pypackage`: https://github.com/audreyr/cookiecutter-pypackage
