%:
	ruby $@.rb < ${shell echo "${@}" | sed -E -e "s/^([0-9]+)p[0-9]$$/\1/"}.in

%s:
	ruby ${shell echo "${@}" | sed -E -e "s/s//"}.rb < sample.in
