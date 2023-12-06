import { processTest, populateTransaction } from "../test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "mumbai_disable_token_guardian"; // <= Name of the test
const testDirSuffix = "mumbai_disable_token_guardian"; // <= directory to compare device snapshots to
const testNetwork = "mumbai";
const signedPlugin = false;

const contractAddr = "0xc1e77ee73403b8a7478884915aa599932a677870"; // <= Address of the smart contract
const chainID = 1;

const inputData =
  "0x2248f76d";
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
