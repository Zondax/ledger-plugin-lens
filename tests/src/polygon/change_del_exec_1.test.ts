import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "polyhub_change_del_exec_1"; // <= Name of the test
const testDirSuffix = "hub_change_del_exec_1"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xdb46d1dc155634fbc732f92e853b10b288ad5a1d"; // <= Address of the smart contract
const chainID = 1;

// https://polygonscan.com/address/0xDb46d1Dc155634FbC732f92E853b10B288AD5a1d#writeProxyContract
const inputData =
  "0x51c3659c000000000000000000000000000000000000000000000000000000000000007700000000000000000000000000000000000000000000000000000000000000A000000000000000000000000000000000000000000000000000000000000000E00000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000006c1e1bc39b13f9e0af9424d76de899203f47755f00000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000001";
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
    steps: 11, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 8, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 8, // <= Define the number of steps for this test case and this device
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
