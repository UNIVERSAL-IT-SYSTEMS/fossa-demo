/*********************************************************************
  PicoTCP. Copyright (c) 2015 Altran Intelligent Systems Belgium NV.
  Some rights reserved.
  See LICENSE and COPYING for usage.
  Do not redistribute without a written permission by the Copyright
  holders.

  Description: Generic Ethernet PHY register defines

  Authors: Maxime Vincent

 *********************************************************************/

#ifndef _PICO_DEV_PHY_GENERIC_H_
#define _PICO_DEV_PHY_GENERIC_H_

/*
 * Well-known PHY-identifiers
 */
#define PHY_KSZ8021_ID    0x00221556
#define PHY_KS8721_ID     0x00221610
#define PHY_DP83848I_ID   0x20005C90
#define PHY_LAN8710A_ID   0x0007C0F1
#define PHY_DM9161_ID     0x0181B8A0
#define PHY_AM79C875_ID   0x00225540
#define PHY_STE101P_ID    0x00061C50

/*
 * Generic PHY registers.
 * Not all registers are present on all PHYs.
 */
#define PHY_BMCTRL              0x00    /**< Basic mode control register.   */
#define PHY_BMSTAT              0x01    /**< Basic mode status register.    */
#define PHY_PHYID1              0x02    /**< PHYS ID 1.                     */
#define PHY_PHYID2              0x03    /**< PHYS ID 2.                     */
#define PHY_ANADV               0x04    /**< Advertisement control reg.     */
#define PHY_LPA                 0x05    /**< Link partner ability reg.      */
#define PHY_ANEXP               0x06    /**< Expansion register.            */
#define PHY_ANNXTP              0x07    /**< Auto-negotiation Next Page reg */

/*
 * Basic mode control register.
 */
#define BMCTRL_RESV               0x007f  /**< Unused.                        */
#define BMCTRL_CTST               0x0080  /**< Collision test                 */
#define BMCTRL_FULLDPLX           0x0100  /**< Full duplex                    */
#define BMCTRL_ANRESTART          0x0200  /**< Auto negotiation restart       */
#define BMCTRL_ISOLATE            0x0400  /**< Disconnect DP83840 from MII    */
#define BMCTRL_PDOWN              0x0800  /**< Powerdown                      */
#define BMCTRL_ANENABLE           0x1000  /**< Enable auto negotiation        */
#define BMCTRL_SPEED100           0x2000  /**< Select 100Mbps                 */
#define BMCTRL_LOOPBACK           0x4000  /**< TXD loopback                   */
#define BMCTRL_RESET              0x8000  /**< Reset                          */

/*
 * Basic mode status register.
 */
#define BMSTAT_ERCAP              0x0001  /**< Ext-reg capability.            */
#define BMSTAT_JCD                0x0002  /**< Jabber detected.               */
#define BMSTAT_LSTATUS            0x0004  /**< Link status.                   */
#define BMSTAT_ANEGCAPABLE        0x0008  /**< Able to do auto-negotiation.   */
#define BMSTAT_RFAULT             0x0010  /**< Remote fault detected.         */
#define BMSTAT_ANEGCOMPLETE       0x0020  /**< Auto-negotiation complete.     */
#define BMSTAT_MFPRESUPPCAP       0x0040  /**< Able to suppress preamble.     */
#define BMSTAT_10HALF             0x0800  /**< Can do 10mbps, half-duplex.    */
#define BMSTAT_10FULL             0x1000  /**< Can do 10mbps, full-duplex.    */
#define BMSTAT_100HALF            0x2000  /**< Can do 100mbps, half-duplex.   */
#define BMSTAT_100FULL            0x4000  /**< Can do 100mbps, full-duplex.   */
#define BMSTAT_100BASE4           0x8000  /**< Can do 100mbps, 4k packets.    */

/*
 * Advertisement control register.
 */
#define ANADV_SLCT          0x001f  /**< Selector bits.                 */
#define ANADV_CSMA          0x0001  /**< Only selector supported.       */
#define ANADV_10HALF        0x0020  /**< Try for 10mbps half-duplex.    */
#define ANADV_10FULL        0x0040  /**< Try for 10mbps full-duplex.    */
#define ANADV_100HALF       0x0080  /**< Try for 100mbps half-duplex.   */
#define ANADV_100FULL       0x0100  /**< Try for 100mbps full-duplex.   */
#define ANADV_100BASE4      0x0200  /**< Try for 100mbps 4k packets.    */
#define ANADV_PAUSE_CAP     0x0400  /**< Try for pause.                 */
#define ANADV_PAUSE_ASYM    0x0800  /**< Try for asymetric pause.       */
#define ANADV_RESV          0x1000  /**< Unused.                        */
#define ANADV_RFAULT        0x2000  /**< Say we can detect faults.      */
#define ANADV_LPACK         0x4000  /**< Ack link partners response.    */
#define ANADV_NPAGE         0x8000  /**< Next page bit.                 */

#define ANADV_FULL          (ANADV_100FULL | ANADV_10FULL | ANADV_CSMA)
#define ANADV_ALL           (ANADV_10HALF | ANADV_10FULL | ANADV_100HALF | ANADV_100FULL)

/*
 * Link partner ability register
 */
#define LPA_SLCT                0x001f  /**< Same as advertise selector.    */
#define LPA_10HALF              0x0020  /**< Can do 10mbps half-duplex.     */
#define LPA_10FULL              0x0040  /**< Can do 10mbps full-duplex.     */
#define LPA_100HALF             0x0080  /**< Can do 100mbps half-duplex.    */
#define LPA_100FULL             0x0100  /**< Can do 100mbps full-duplex.    */
#define LPA_100BASE4            0x0200  /**< Can do 100mbps 4k packets.     */
#define LPA_PAUSE_CAP           0x0400  /**< Can pause.                     */
#define LPA_PAUSE_ASYM          0x0800  /**< Can pause asymetrically.       */
#define LPA_RFAULT              0x2000  /**< Link partner faulted.          */
#define LPA_LPACK               0x4000  /**< Link partner acked us.         */
#define LPA_NPAGE               0x8000  /**< Next page bit.                 */

#define LPA_DUPLEX              (LPA_10FULL | LPA_100FULL)
#define LPA_100                 (LPA_100FULL | LPA_100HALF | LPA_100BASE4)

#endif /* _PICO_DEV_PHY_GENERIC_H_ */

