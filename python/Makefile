#

PYLINT=pylint
PYCODESTYLE=pycodestyle

FILES=rfidler.py RFIDler/__init__.py

all: pylint

lint: pylint

pylint:
	@for f in ${FILES} ; do \
		echo checking $${f} ; \
		${PYLINT} -E $${f} ; \
		${PYCODESTYLE} $${f} ; \
	done

install:
	pip3 install .

uninstall:
	pip3 uninstall RFIDler

clean:
	@/bin/rm -fr *.pyc RFIDler/*.pyc RFIDler/__pycache__
	@/bin/rm -fr dist build RFIDler.egg-info
