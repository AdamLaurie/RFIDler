from distutils.core import setup, Extension

packages= ['RFIDler']

scripts= ['rfidler.py']

setup  (name        = 'RFIDler',
        version     = '1.0',
        description = "RFIDler Software Defined RFID device python wrapper",
        author = 'Adam Laurie',
        author_email = 'adam@apaerurelabs.com',
	packages= packages,
	scripts= scripts
       )

