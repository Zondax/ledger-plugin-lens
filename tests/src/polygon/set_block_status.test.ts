import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "polyhub_set_block_status"; // <= Name of the test
const testDirSuffix = "hub_set_block_status"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xdb46d1dc155634fbc732f92e853b10b288ad5a1d"; // <= Address of the smart contract
const chainID = 1;

// https://polygonscan.com/address/0xDb46d1Dc155634FbC732f92E853b10B288AD5a1d#writeProxyContract
const inputData =
  "0xfb827e820000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000006000000000000000000000000000000000000000000000000000000000000000a00000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000";
// Create serializedTx and remove the "0x" prefix
const value = "3.1";
const serializedTx = populateTransaction(
  contractAddr,
  inputData,
  chainID,
  value
);
const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 4, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 4, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 4, // <= Define the number of steps for this test case and this device
  },
];

devices.forEach((device) =>
  processTest(
    device,
    contractName,
    testLabel,
    testDirSuffix,
    "",
    signedPlugin,
    serializedTx,
    testNetwork
  )
);
