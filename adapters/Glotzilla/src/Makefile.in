@SET_MAKE@

SUBDIRS = Glue
RECURSIVE_TARGETS = all-recursive clean-recursive install-recursive

all: all-recursive

clean: clean-recursive

install: install-recursive

$(RECURSIVE_TARGETS):
	     @failcom='exit 1'; \
	            for f in x $$MAKEFLAGS; do \
	              case $$f in \
	                *=* | --[!k]*);; \
	                *k*) failcom='fail=yes';; \
	              esac; \
	            done; \
	            dot_seen=no; \
	            target=`echo $@ | sed s/-recursive//`; \
	            list='$(SUBDIRS)'; for subdir in $$list; do \
	              echo "Making $$target in $$subdir"; \
	              if test ! "$$subdir" = "."; then \
	                local_target="$$target"; \
                        echo "$$target $$local_target"; \
	              fi; \
	              (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	              || eval $$failcom; \
	            done; \
	            test -z "$$fail"

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
