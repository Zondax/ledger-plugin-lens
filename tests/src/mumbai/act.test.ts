import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "mumbai_hub_act"; // <= Name of the test
const testDirSuffix = "hub_act"; // <= directory to compare device snapshots to
const testNetwork = "mumbai";
const signedPlugin = false;

const contractAddr = "0xc1e77ee73403b8a7478884915aa599932a677870"; // <= Address of the smart contract
const chainID = 1;

// From : https://mumbai.polygonscan.com/tx/0x1aefca366d6e1144ad65732cc95752a0ff13f804e08858802d81e1c2a498c058
const inputData =
  "0xc5d5d96a000000000000000000000000000000000000000000000000000000000000002000000000000000000000000000000000000000000000000000000000000000330000000000000000000000000000000000000000000000000000000000000069000000000000000000000000000000000000000000000000000000000000001d00000000000000000000000000000000000000000000000000000000000000e000000000000000000000000000000000000000000000000000000000000001000000000000000000000000005fe7918c3ef48e6c5fd79dd22a3120a3c4967ac200000000000000000000000000000000000000000000000000000000000001200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000a000000000000000000000000098dad8b389417a5a7d971d7f83406ac7c646a8e20000000000000000000000000000000000000000000000000000000000000040000000000000000000000000000000000000000000000000000000000000004000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
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
    steps: 6, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 6, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 6, // <= Define the number of steps for this test case and this device
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
