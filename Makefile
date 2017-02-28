ui:
	test -d data/homie || mkdir data/homie/ui_bundle.gz && curl -sL http://setup.homie-esp8266.marvinroger.fr/ui_bundle.gz -o data/homie/ui_bundle.gz
build:
	docker run --rm $$(docker build -q -f Dockerfile.build .) /usr/local/bin/get-artifact > homie-controller
	md5sum homie-intercom > homie-intercom.md5
	sha512sum homie-intercom > homie-intercom.sha512

