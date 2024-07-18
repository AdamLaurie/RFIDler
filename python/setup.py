from distutils.core import setup, Extension
from RFIDler import __VERSION__

packages= ['RFIDler']

scripts= ['rfidler.py']

setup  (name        = 'RFIDler',
        version     = __VERSION__,
        description = "RFIDler Software Defined RFID device python wrapper",
        author = 'Adam Laurie',
        author_email = 'adam@apaerurelabs.com',
        git='https://github.com/AdamLaurie/RFIDler',
	packages= packages,
        requires_python='>=3.5',
	scripts= scripts,
        install_requires=[
            'matplotlib',
            'numpy',
            'pyserial',
            ],
    )


# pyserial:
# https://stackoverflow.com/questions/64383756/has-python-package-serial-been-renamed-to-pyserial
