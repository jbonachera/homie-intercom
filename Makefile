ui:
	test -d data/homie || mkdir data/homie/ui_bundle.gz && curl -sL http://setup.homie-esp8266.marvinroger.fr/ui_bundle.gz -o data/homie/ui_bundle.gz

