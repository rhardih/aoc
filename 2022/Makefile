%:
	day=${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}; \
	ruby $@.rb < $$day.in

%s:
	ruby ${shell echo "${@}" | sed -E -e "s/s//"}.rb < sample.in

%awk:
	day=${shell echo "${@}" | sed -E -e "s/^([0-9]+)awk/\1/"}; \
	gawk -f $$day.awk < $$day.in
