import subprocess
import sys
import os

ARCHIVE = "asap7sc6t_AO_RVT_TT_ccs_211010.lib.7z"
TEMP_LIB = "temp.lib"
TEMP_PRUNE_LIB = "temp_prune.lib"
PARSER = "../build/prune"

CCS_REGEX = (
    "output_current_rise|output_current_fall|"
    "receiver_capacitance1_rise|receiver_capacitance1_fall|"
    "receiver_capacitance2_rise|receiver_capacitance2_fall|"
    "output_current_power_rise|output_current_power_fall|"
    "noise_immunity_high|noise_immunity_low|"
    "noise_immunity_above_high|noise_immunity_below_low|"
    "propagated_noise_high|propagated_noise_low|"
    "steady_state_current_high|steady_state_current_low|"
    "steady_state_current_tristate|"
    "ccsn_first_stage|ccsn_last_stage|dc_current|"
    "output_current_template|ccsn_first_stage_template|"
    "ccsn_last_stage_template|dc_current_template|"
    "noise_lut_template|propagation_lut_template"
)

def die(msg):
    print("ERROR:", msg)
    sys.exit(1)

# ------------------------------------------------------------
# 1. Extract .7z -> temp.lib
# ------------------------------------------------------------
print("Extracting archive...")

cmd_extract = f"7z x -so {ARCHIVE} > {TEMP_LIB}"
proc = subprocess.run(cmd_extract, shell=True)

if proc.returncode != 0:
    die("7z extraction failed")

if not os.path.exists(TEMP_LIB):
    die("temp.lib was not created")

# ------------------------------------------------------------
# 2. Run prune: temp.lib -> temp_prune.lib
# ------------------------------------------------------------
print("Running prune...")

with open(TEMP_PRUNE_LIB, "w") as out_file:
    proc = subprocess.run(
        [PARSER, TEMP_LIB],
        stdout=out_file,
        stderr=subprocess.PIPE,
        text=True
    )

if proc.returncode != 0:
    print("Parser stderr:")
    print(proc.stderr)
    die("prune failed")

if not os.path.exists(TEMP_PRUNE_LIB):
    die("temp_prune.lib was not created")

# ------------------------------------------------------------
# 3. Grep for forbidden CCS keywords in temp_prune.lib
# ------------------------------------------------------------
print("Scanning for forbidden CCS keywords...")

cmd_grep = f"grep -nE '{CCS_REGEX}' {TEMP_PRUNE_LIB}"
proc = subprocess.run(
    cmd_grep,
    shell=True,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    text=True
)

# grep return codes:
# 0 = match found
# 1 = no match
# 2 = error

if proc.returncode == 0:
    print("ERROR: Forbidden CCS keyword found:")
    print(proc.stdout)
    sys.exit(1)

elif proc.returncode == 1:
    print("OK: No CCS keywords found in temp_prune.lib")
    sys.exit(0)

else:
    print("GREP FAILED:")
    print(proc.stderr)
    sys.exit(2)

