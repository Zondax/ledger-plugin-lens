import { processTest, populateTransaction } from "./test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "poly_hub_unlink"; // <= Name of the test
const testDirSuffix = "hub_unlink"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0x9cd0d07ab772e42ed3497dd379360dabcd94352a"; // <= Address of the smart contract
const chainID = 1;

// From : https://mumbai.polygonscan.com/address/0x9cD0d07AB772e42ed3497DD379360daBcD94352A#writeProxyContract
const inputData =
  "0x0c65b39d000000000000000000000000000000000000000000000000000000000000023700000000000000000000000000000000000000000000000000000000000001c8";
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
