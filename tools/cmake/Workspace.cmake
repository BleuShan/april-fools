include_guard()

# Global environment setup
include(WorkspaceUtilities)
include(VcpkgHelpers)
include(WorkspaceHelpers)

# Globals
set(WORKSPACE_TEST_SUFFIX_REGEX "([-_]t|T)ests?$")

setup_vcpkg()
