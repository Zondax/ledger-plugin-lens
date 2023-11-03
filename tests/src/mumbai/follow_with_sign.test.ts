import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "mumbai_hub_follow_with_sign"; // <= Name of the test
const testDirSuffix = "hub_follow_with_sign"; // <= directory to compare device snapshots to
const testNetwork = "mumbai";
const signedPlugin = false;

const contractAddr = "0xc1e77ee73403b8a7478884915aa599932a677870"; // <= Address of the smart contract
const chainID = 1;

// From : https://mumbai.polygonscan.com/tx/0x8b55140ee84401822408b83ecabd2a0e3beea5b412713457e14bc588f91a3019
const inputData =
  "0x4d7b35a000000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000120000000000000000000000000000000000000000000000000000000000000016000000000000000000000000000000000000000000000000000000000000001a000000000000000000000000065eb6a45b7bc407baad8612e3168ab5b1887e8fd000000000000000000000000000000000000000000000000000000000000001ca54e21c601244958d6dd49a30001a7910e49e239f318b3128de66336eb271bb56e621215868b1190b221195fb0e18d3c28ead025f1aa35fe745167b6a5ee50c800000000000000000000000000000000000000000000000000000000650d88560000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000000";
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
    steps: 5, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanox",
    label: "Nano X",
    steps: 5, // <= Define the number of steps for this test case and this device
  },
  {
    name: "nanosp",
    label: "Nano S+",
    steps: 5, // <= Define the number of steps for this test case and this device
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
