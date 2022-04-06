include_guard()

# Global environment setup
include(WorkspaceUtilities)
include(VcpkgHelpers)
include(WorkspaceHelpers)
include(GenerateFiles)

# Globals
set(WORKSPACE_TEST_SUFFIX_REGEX "([-_]t|T)ests?$")
set(
  WORKSPACE_SUPPORTED_TARGET_OSES
  macOS
  Windows
  CACHE
  INTERNAL
  "Allowed Target OSes"
)

setup_vcpkg()
