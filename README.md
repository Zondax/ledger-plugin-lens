# Ledger Lens Plugin

This is a plugin for the Ethereum application which helps parsing and displaying relevant information when signing a lens smart contract.

## Prerequisite

Clone the plugin to a new folder.

```shell
git clone https://github.com/libertify/ledger-plugin-lens.git
```

Then in the same folder clone the app-ethereum.

```shell
git clone --recurse-submodules https://github.com/LedgerHQ/app-ethereum.git     #app-ethereum
```

## Documentation

Need more information about the interface, the architecture, or general stuff about ethereum plugins? You can find more about them in the [ethereum-app documentation](https://github.com/LedgerHQ/app-ethereum/blob/master/doc/ethapp_plugins.adoc).

## Smart Contracts

Smart contracts covered by this plugin are:

|  Network | Smart Contract                 | Smart Contract Address |
| -------- | ------------------------------ | ---------------------- |
| Mumbai | LensHub Proxy        | [0xC1E77eE73403B8a7478884915aA599932A677870](https://mumbai.polygonscan.com/address/0xC1E77eE73403B8a7478884915aA599932A677870#code) |
| Mumbai | TokenHandleRegistry Proxy        | [0x9cD0d07AB772e42ed3497DD379360daBcD94352A](https://mumbai.polygonscan.com/address/0x9cD0d07AB772e42ed3497DD379360daBcD94352A) |
| Mumbai | LensHandle Proxy        | [0xc3a1fabd7f8d290f7b0C45AA88af6e9c9E267843](https://mumbai.polygonscan.com/address/0xc3a1fabd7f8d290f7b0C45AA88af6e9c9E267843) |
| Polygon | LensHub         | [0xDb46d1Dc155634FbC732f92E853b10B288AD5a1d](https://polygonscan.com/address/0xDb46d1Dc155634FbC732f92E853b10B288AD5a1d) |
| Polygon | TokenHandleRegistry         | [0xD4F2F33680FCCb36748FA9831851643781608844](https://polygonscan.com/address/0xD4F2F33680FCCb36748FA9831851643781608844#code) |
| Polygon | LensHandle        | [0xe7E7EaD361f3AaCD73A61A9bD6C10cA17F38E945](https://polygonscan.com/address/0xe7E7EaD361f3AaCD73A61A9bD6C10cA17F38E945) |

...

## Functions implemented

|    Function                           | Selector   | Displayed Parameters   |
| ---                                   | ---        |  ---                   |
| act                                   | 0xc5d5d96a | <table> <tbody> <tr><td><code>uint256 pubprofileId</code></td></tr> <tr><td><code>uint256 publicationId</code></td></tr> <tr><td><code>uint256 actorprofileId</code></td></tr> </tbody> </table>|
| act_with_sign                         | 0xc86642c7 | <table> <tbody> <tr><td><code>uint256 pubprofileId</code></td></tr> <tr><td><code>uint256 publicationId</code></td></tr> <tr><td><code>uint256 actorprofileId</code></td></tr><tr><td><code>uint256 signatureDeadline</code></td></tr> </tbody> </table>|
| burn                                  | 0x42966c68 | <table> <tbody> <tr><td><code>uint256 token ID</code></td></tr></tbody> </table>|
| change_delegate_exe_config          | 0x51c3659c | <table> <tbody> <tr><td><code>uint256 delegatorProfileId</code></td></tr> <tr><td><code>address delegatedExecutor</code></td></tr>  <tr><td><code>bool approval</code></td></tr>  <tr><td><code>uint256 configNumber</code></td></tr> <tr><td><code>uint256 switchToGivenConfig</code></td></tr> </tbody> </table>|
| change_delegate_exe_config          | 0xc1f4b40a |<table> <tbody> <tr><td><code>uint256 delegatorProfileId</code></td></tr> <tr><td><code>address delegatedExecutors</code></td></tr>  <tr><td><code>bool approval</code></td></tr> </tbody> </table>|
| change_delegate_exe_config__with_sign | 0x4926c4ed |<table> <tbody> <tr><td><code>uint256 delegatorProfileId</code></td></tr> <tr><td><code>address delegatedExecutor</code></td></tr>  <tr><td><code>bool approval</code></td></tr>  <tr><td><code>uint256 configNumber</code></td></tr> <tr><td><code>uint256 signatureDeadline</code></td></tr> </tbody> </table>|
| collect                               | 0x4727ce3a |<table> <tbody> <tr><td><code>uint256 publicationCollectedProfileId</code></td></tr> <tr><td><code>uint256 publicationCollectedId</code></td></tr> <tr><td><code>uint256 collectorProfileId</code></td></tr> </tbody> </table>|
| collect_with_sign                     | 0xb7902e73 |<table> <tbody> <tr><td><code>uint256 publicationCollectedProfileId</code></td></tr> <tr><td><code>uint256 publicationCollectedId</code></td></tr> <tr><td><code>uint256 collectorProfileId</code></td></tr> <tr><td><code>uint256 signatureDeadline</code></td></tr> </tbody> </table>|
| comment                               | 0xb273b4a7 |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>uint256 profile_id_pointed</code></td></tr> <tr><td><code>uint256 pubid_pointed</code></td></tr> </tbody> </table>|
| comment_with_sign                     | 0xb42df51a |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>uint256 profile_id_pointed</code></td></tr> <tr><td><code>uint256 pubid_pointed</code></td></tr>  <tr><td><code>uint256 signatureDeadline</code></td></tr> </tbody> </table>|
| create_profile                        | 0x560a4db1 |<table> <tbody> <tr><td><code>address to</code></td></tr> <tr><td><code>address followMododule</code></td></tr> </tbody> </table>|
| follow                                | 0x4b7312a9 |<table> <tbody> <tr><td><code>uint256 followerProfileId</code></td></tr></tbody> </table>|
| follow_with_sign                      | 0x4d7b35a0 |<table> <tbody> <tr><td><code>uint256 followerProfileId</code></td></tr><tr><td><code>uint256 signatureDeadline</code></td></tr> </tbody> </table>|
| link                                  | 0x86CF48E7 |<table> <tbody> <tr><td><code>uint256 handle_id</code></td></tr> <tr><td><code>uint256 profile_id</code></td></tr></tbody> </table>|
| link_with_sig                         | 0x7e502fe0 |<table> <tbody> <tr><td><code>uint256 handle_id</code></td></tr> <tr><td><code>uint256 profile_id</code></td></tr></tbody> <tr><td><code>uint256 signatureDeadline</code></td></tr></table>|
| mint                                  | 0xf08e8f5e |<table> <tbody> <tr><td><code>uint256 to</code></td></tr></tbody> </table>|
| mirror                                | 0xf90604d1 |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>uint256 profile_id_pointed</code></td></tr> <tr><td><code>uint256 pubid_pointed</code></td></tr> </tbody> </table>|
| mirror_with_sign                      | 0xe6a402b5 |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>uint256 profile_id_pointed</code></td></tr> <tr><td><code>uint256 pubid_pointed</code></td></tr>  <tr><td><code>uint256 signatureDeadline</code></td></tr> </tbody> </table>|
| post                                  | 0x66b0dcd3 |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>address referenceModule</code></td></tr></tbody> </table>|
| post_with_sign                        | 0x907cd7d2 |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>address referenceModule</code></td></tr> <tr><td><code>uint256 signatureDeadline</code></td></tr> </tbody> </table>|
| quote                                 | 0xF0ba35f0 |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>uint256 profile_id_pointed</code></td></tr> <tr><td><code>uint256 pubid_pointed</code></td></tr> </tbody> </table>|
| quote_with_sign                       | 0x65f29f27 |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>uint256 profile_id_pointed</code></td></tr> <tr><td><code>uint256 pubid_pointed</code></td></tr>  <tr><td><code>uint256 signatureDeadline</code></td></tr> </tbody> </table>|
| set_block_status                      | 0xfb827e82 |<table> <tbody> <tr><td><code>uint256 byProfileId</code></td></tr></tbody> </table>|
| set_block_status_with_sig             | 0xC6d45944 |<table> <tbody> <tr><td><code>uint256 byProfileId</code></td></tr> <tr><td><code>uint256 signatureDeadline</code></td></tr> </tbody> </table>|
| set_follow_mod                        | 0x6dea40b3 |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>address followModule</code></td></tr></tbody> </table>|
| set_follow_mod_with_sig               | 0xce30bb4f |<table> <tbody> <tr><td><code>uint256 profile_id</code></td></tr> <tr><td><code>address followModule</code></td></tr> <tr><td><code>uint256 signatureDeadline</code></td></tr></tbody> </table>|
| set_profile_metadata                  | 0xefe4fd83 |<table> <tbody> <tr><td><code>uint256 profileId</code></td></tr></tbody> </table>|
| set_profile_metadata_with_sign        | 0x6d0fd658 |<table> <tbody> <tr><td><code>uint256 profileId</code></td></tr>  <tr><td><code>uint256 signatureDeadline</code></td></tr></tbody> </table>|
| unfollow                              | 0x815ed04a |<table> <tbody> <tr><td><code>uint256 unfollowerProfileId</code></td></tr></tbody> </table>|
| unfollow_with_sign                    | 0x809d8947 |<table> <tbody> <tr><td><code>uint256 unfollowerProfileId</code></td></tr> <tr><td><code>uint256 signatureDeadline</code></td></tr></tbody> </table>|
| white_list_profile_create             | 0x20905506 |<table> <tbody> <tr><td><code>address profileCreator</code></td></tr> <tr><td><code>bool whitelist</code></td></tr></tbody> </table>|
| unlink                                | 0x0c65b39d |<table> <tbody> <tr><td><code>uint256 handle_id</code></td></tr> <tr><td><code>uint256 profile_id</code></td></tr></tbody> </table>|
| unlink_with_sig                       | 0x825ab164 |<table> <tbody> <tr><td><code>uint256 handle_id</code></td></tr> <tr><td><code>uint256 profile_id</code></td></tr></tbody> <tr><td><code>uint256 signatureDeadline</code></td></tr></table>|
| disable_token_guardian                | 0x2248f76d | no parameters |

For both change_delegate_exe_config functions and change_delegate_exe_config_with_sign, LENS plugin will only support signing transactions with 1 delegated executor and 1 approval.

## Build

To build the plugin, go to your folder with Ethereum app and plugin. Open a new terminal window and run:
```shell
sudo docker run --rm -ti -v "$(realpath .):/app" --user $(id -u $USER):$(id -g $USER) ghcr.io/ledgerhq/ledger-app-builder/ledger-app-dev-tools:latest
```

In the container, go to the plugin repository, then to the tests/ folder.
```shell
cd ledger-plugin-lens/tests
./build_local_test_elfs.sh. 
```


## Tests

To test the plugin go to the tests folder from the "app-plugin-ens" and run the script "test"
```shell
cd ledger-plugin-lens/tests         # go to the tests folder in app-plugin-ens
yarn test                       # run the script test
```
