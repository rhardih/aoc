%:
	day=${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}; \
	ruby $@.rb < $$day.in

%s:
	day=${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]s$$/\1/"}; \
	ruby ${shell echo "${@}" | sed -E -e "s/s//"}.rb < $$day.example.in

%awk:
	day=${shell echo "${@}" | sed -E -e "s/^([0-9]+)awk/\1/"}; \
	gawk -f $$day.awk < $$day.in
