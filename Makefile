2015:
	@cd 2015 && make $(filter-out $@,$(MAKECMDGOALS))

2016:
	@cd 2016 && make $(filter-out $@,$(MAKECMDGOALS))

2017:
	@cd 2017 && make $(filter-out $@,$(MAKECMDGOALS))

2018:
	@cd 2018 && make $(filter-out $@,$(MAKECMDGOALS))

2019:
	@cd 2019 && make $(filter-out $@,$(MAKECMDGOALS))

%:
	@:

.PHONY: 2015 2016 2017 2018 2019
