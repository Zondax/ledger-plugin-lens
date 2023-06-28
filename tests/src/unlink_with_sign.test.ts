import { processTest, populateTransaction } from "./test.fixture";

const contractName = "TransparentUpgradeableProxy"; // <= Name of the smart contract

const testLabel = "poly_hub_unlink_with_sign"; // <= Name of the test
const testDirSuffix = "hub_unlink_with_sign"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0x9cd0d07ab772e42ed3497dd379360dabcd94352a"; // <= Address of the smart contract
const chainID = 1;

// From : https://mumbai.polygonscan.com/address/0x9cD0d07AB772e42ed3497DD379360daBcD94352A#writeProxyContract
const inputData =
  "0x825ab164000000000000000000000000000000000000000000000000000000000000007b000000000000000000000000000000000000000000000000000000000000037a000000000000000000000000b728dc8883dc872a58e20f1a0bd09e39ec8e51f5000000000000000000000000000000000000000000000000000000000000001c4f14b92b4be8679c61b3974162d524021f478d0b068621191101fe2aed6158c760fa7e36074ff87af1a85125b0ab93ad045dc9163542fc80c6f8a212e5542cd0000000000000000000000000000000000000000000000000000000006506ffa5";
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
