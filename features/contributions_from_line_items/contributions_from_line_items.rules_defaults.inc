<?php
/**
 * @file
 * contributions_from_line_items.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function contributions_from_line_items_default_rules_configuration() {
  $items = array();
  $items['rules_create_contribution_from_line_item'] = entity_import('rules_config', '{ "rules_create_contribution_from_line_item" : {
      "LABEL" : "Create Contribution From Line Item",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "CiviCRM", "Commerce Checkout" ],
      "REQUIRES" : [ "rules", "commerce_civicrm_rules" ],
      "USES VARIABLES" : {
        "line_item" : { "label" : "Line Item", "type" : "commerce_line_item" },
        "order" : { "label" : "Commerce Order", "type" : "commerce_order" },
        "civicrm_contact" : { "label" : "CiviCRM contact", "type" : "civicrm_contact" },
        "civicrm_contribution_id" : {
          "label" : "CiviCRM Contribution ID",
          "type" : "integer",
          "parameter" : false
        }
      },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "line-item" ], "type" : "commerce_line_item" } },
        { "entity_is_of_bundle" : {
            "entity" : [ "line-item" ],
            "type" : "commerce_line_item",
            "bundle" : { "value" : { "product_discount" : "product_discount", "product" : "product" } }
          }
        }
      ],
      "DO" : [
        { "commerce_civicrm_rules_create_contribution_by_line_item" : {
            "USING" : {
              "civicrm_contact" : [ "civicrm_contact" ],
              "commerce_order" : [ "order" ],
              "commerce_line_item" : [ "line-item" ]
            },
            "PROVIDE" : { "integer" : { "created_civicrm_contribution_id" : "Created CiviCRM Contribution ID" } }
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "created_civicrm_contribution_id" ]
    }
  }');
  $items['rules_create_membership_from_line_item'] = entity_import('rules_config', '{ "rules_create_membership_from_line_item" : {
      "LABEL" : "Create Membership From Line Item",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "line_item" : { "label" : "Line Item", "type" : "commerce_line_item" },
        "civicrm_contribution" : { "label" : "CiviCRM Contribution", "type" : "civicrm_contribution" },
        "civicrm_membership" : {
          "label" : "CiviCRM Membership",
          "type" : "civicrm_membership",
          "parameter" : false
        }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "line-item" ],
            "type" : "commerce_line_item",
            "bundle" : { "value" : { "product_discount" : "product_discount", "product" : "product" } }
          }
        },
        { "entity_has_field" : {
            "entity" : [ "line-item:commerce-product" ],
            "field" : "field_civicrm_membership_type"
          }
        },
        { "entity_has_field" : {
            "entity" : [ "line-item:commerce-product" ],
            "field" : "field_civicrm_membership_num_ter"
          }
        }
      ],
      "DO" : [
        { "component_rules_create_paid_civicrm_membership" : {
            "USING" : {
              "civicrm_contact" : [ "civicrm-contribution:contact-id-contact" ],
              "civicrm_contribution" : [ "civicrm_contribution" ],
              "civicrm_membership_type_id" : [ "line-item:commerce-product:field-civicrm-membership-type:id" ],
              "civicrm_membership_num_terms" : [ "line-item:commerce-product:field-civicrm-membership-num-ter" ]
            },
            "PROVIDE" : { "civicrm_membership" : { "created_civicrm_membership" : "Civicrm Membership" } }
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "civicrm_membership" ]
    }
  }');
  $items['rules_create_paid_civicrm_membership'] = entity_import('rules_config', '{ "rules_create_paid_civicrm_membership" : {
      "LABEL" : "Create Paid CiviCRM Membership",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "CiviCRM", "Membership" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "civicrm_contact" : { "label" : "CiviCRM Contact", "type" : "civicrm_contact" },
        "civicrm_contribution" : { "label" : "CiviCRM Contribution", "type" : "civicrm_contribution" },
        "civicrm_membership_type_id" : { "label" : "CiviCRM Membership Type ID", "type" : "integer" },
        "civicrm_membership_num_terms" : { "label" : "CiviCRM Membership  Number of terms", "type" : "integer" },
        "civicrm_membership" : {
          "label" : "Civicrm Membership",
          "type" : "civicrm_membership",
          "parameter" : false
        }
      },
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "civicrm_membership",
              "param_membership_type_id" : [ "civicrm-membership-type-id" ],
              "param_contact_id" : [ "civicrm-contact:id" ],
              "param_civicrm_contribution" : [ "civicrm-contribution" ],
              "param_status_id" : [ "" ],
              "param_is_override" : [ "" ],
              "param_owner_membership_id" : [ "" ],
              "param_max_related" : [ "" ],
              "param_contribution_recur_id" : [ "" ],
              "param_id" : [ "" ],
              "param_source" : [ "" ],
              "param_is_test" : [ "" ],
              "param_is_pay_later" : [ "" ],
              "param_campaign_id" : [ "" ],
              "param_num_terms" : [ "civicrm-membership-num-terms" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "civicrm_membership" ]
    }
  }');
  $items['rules_create_participant_from_line_item'] = entity_import('rules_config', '{ "rules_create_participant_from_line_item" : {
      "LABEL" : "Create Participant From Line Item",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "line_item" : { "label" : "Line Item", "type" : "commerce_line_item" },
        "civicrm_contribution" : { "label" : "CiviCRM Contribution", "type" : "civicrm_contribution" },
        "civicrm_participant" : {
          "label" : "CiviCRM Participant",
          "type" : "civicrm_participant",
          "parameter" : false
        }
      },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "line-item" ],
            "type" : "commerce_line_item",
            "bundle" : { "value" : { "product_discount" : "product_discount", "product" : "product" } }
          }
        },
        { "entity_has_field" : {
            "entity" : [ "line-item:commerce-product" ],
            "field" : "field_civicrm_event"
          }
        }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "civicrm_participant",
              "param_event_id" : [ "line-item:commerce-product:field-civicrm-event:id" ],
              "param_contact_id" : [ "civicrm-contribution:contact-id" ],
              "param_civicrm_contribution" : [ "civicrm-contribution" ],
              "param_discount_amount" : [ "" ],
              "param_cart_id" : [ "" ],
              "param_must_wait" : [ "" ],
              "param_id" : [ "" ],
              "param_status_id" : [ "" ],
              "param_role_id" : [ "" ],
              "param_source" : [ "" ],
              "param_fee_level" : [ "" ],
              "param_is_test" : [ "" ],
              "param_is_pay_later" : [ "" ],
              "param_registered_by_id" : [ "" ],
              "param_discount_id" : [ "" ],
              "param_fee_currency" : [ "" ],
              "param_campaign_id" : [ "" ],
              "param_custom_4" : [ "" ],
              "custom_4" : [ "" ]
            },
            "PROVIDE" : { "entity_created" : { "participant_created" : "Created Participant" } }
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "civicrm_participant" ]
    }
  }');
  $items['rules_line_item_create_civicrm_contact_and_contribution'] = entity_import('rules_config', '{ "rules_line_item_create_civicrm_contact_and_contribution" : {
      "LABEL" : "Create CiviCRM entities from Commerce Checkout",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "CiviCRM commerce" ],
      "REQUIRES" : [ "civicrm", "rules", "commerce_checkout" ],
      "ON" : { "commerce_checkout_complete" : [] },
      "DO" : [
        { "civicrm_entity_action_load_create_contact" : {
            "USING" : { "user" : [ "commerce-order:owner" ], "email" : [ "" ] },
            "PROVIDE" : { "civicrm_contact" : { "civicrm_contact" : "Created or Loaded CiviCRM Contact" } }
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "civicrm_contact", "id" : [ "civicrm-contact:id" ] },
            "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "commerce-order:commerce-line-items" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "component_rules_create_contribution_from_line_item" : {
                  "USING" : {
                    "line_item" : [ "list-item" ],
                    "order" : [ "commerce-order" ],
                    "civicrm_contact" : [ "entity-fetched" ]
                  },
                  "PROVIDE" : { "integer" : { "created_civicrm_contribution_id" : "CiviCRM Contribution ID" } }
                }
              },
              { "component_rules_create_participant_from_line_item" : {
                  "USING" : {
                    "line_item" : [ "list-item" ],
                    "civicrm_contribution" : [ "created-civicrm-contribution" ]
                  },
                  "PROVIDE" : { "civicrm_participant" : { "civicrm_participant" : "CiviCRM Participant" } }
                }
              },
              { "component_rules_create_membership_from_line_item" : {
                  "USING" : {
                    "line_item" : [ "list-item" ],
                    "civicrm_contribution" : [ "created-civicrm-contribution" ]
                  },
                  "PROVIDE" : { "civicrm_membership" : { "civicrm_membership" : "CiviCRM Membership" } }
                }
              }
            ]
          }
        }
      ]
    }
  }');
  return $items;
}
