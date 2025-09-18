
int brcmf_chip_get_raminfo(struct brcmf_chip *pub)
{
	/*
	 * Core data structures for managing the chip's internal state.
	 * hardware features, and core components.
	 *
	 * struct brcmf_chip. 
	 * 	Public data structure exposing chip hardware features
	 * 	and core components to external drivers.
	 *
	 * so. the structure members will be populated within the following
	 * logical flow
	 * like:
	 * 	Chip ID . BCM43549,BCM4375 ...
	 * 	pmucaps 
	 * 	rambase
	 * 	ramsize
	 *
	 * the most important are still rambase and ramsize. because the 
	 * firmware needs to be written into this space
	 */
	struct brcmf_chip_priv *ci = container_of(pub, struct brcmf_chip_priv,
				pub);
	
	/*
	 * Chip core's private internal structure
	 * for managing the states and configurations of all functional 
	 * cores inside the chip
	 *
	 * typical cores:
	 * 	1. chipcommon core   :Control and base config
	 * 	2. PCIe core	     :Manages PCIe interface communication
	 * 	3. Arm CR4 core      :Main processor core
	 * 	4. 802.11ax MAC Core :Hardware implementation of the WI-FI6 protocol stack
	 * 	5. ......
	 */
	struct brcmf_core_priv *mem_core;

	/*
	 * For identifying and locating internal functional blocks of the chip
	 */
	struct brcmf_core *mem;


}
