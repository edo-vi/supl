file(REMOVE_RECURSE
  "libsupl.pdb"
  "libsupl.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/supl.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
