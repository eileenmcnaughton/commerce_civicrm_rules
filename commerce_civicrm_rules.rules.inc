<?php

/**
 * @file
 * This file contains the Rules hooks and functions necessary to make the order
 * related entity, conditions, events, and actions work.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_civicrm_rules_rules_action_info() {
  $default_financial_type = variable_get('commerce_civicrm_contribution_type', FALSE);
  $actions['commerce_civicrm_rules_create_contribution_by_line_item'] = array(
    'group' => t('Commerce CiviCRM Rules'),
    'label' => t('Create a contribution by contribution Line item'),
    'named parameter' => TRUE,
    'parameter' => array(
      'civicrm_contact' => array('type' => 'civicrm_contact', 'label' => t('CiviCRM Contact')),
      'commerce_order' => array('type' => 'commerce_order', 'label' => t('Order')),
      'commerce_line_item' => array('type' => 'commerce_line_item', 'label' => t('Line Item')),
      'financial_type_id' => array(
        'type' => 'integer',
        'label' => t('Financial Type ID'),
        'default value' => $default_financial_type,
        'optional' => !empty($default_financial_type),
      ),
      'event_id' => array('type' => 'integer', 'label' => t('Registering for Event ID'), 'optional' => TRUE),
      'membership_type_id' => array('type' => 'integer', 'label' => t('Registering for Membership Type ID'), 'optional' => TRUE),
      'quantity' => array('type' => 'integer', 'label' => t('Quantity - number of terms for membership, number of participants for events'), 'optional' => TRUE),
    ),
    'provides' => array(
      'civicrm_contribution_id' => array('type' => 'integer', 'label' => t('CiviCRM Contribution ID')),
      'civicrm_participant_id' => array('type' => 'integer', 'label' => t('CiviCRM Participant ID')),
      'civicrm_membership_id' => array('type' => 'integer', 'label' => t('CiviCRM Membership ID')),
      'list_civicrm_participant_id' => array('type' => 'list:integer', 'label' => t('List of Participant IDs')),
    ),
  );
  foreach (commerce_rules_get_custom_fields('contribution') as $fieldname => $field) {
    $actions['commerce_civicrm_rules_create_contribution_by_line_item']['parameter'][$fieldname] = array(
       'type' => $field['type'], 'label' => $field['label'], 'optional' => TRUE, 'allow null' => TRUE,
    );
  }
  $actions['commerce_civicrm_rules_update_status_by_line_item'] = array(
    'group' => t('Commerce CiviCRM Rules'),
    'label' => t('Update contribution and related entities byLine item'),
    'named parameter' => TRUE,
    'parameter' => array(
      'commerce_order' => array('type' => 'commerce_order', 'label' => t('Order')),
      'commerce_line_item' => array('type' => 'commerce_line_item', 'label' => t('Line Item')),
    ),
  );
  return $actions;
}

/**
 * @param string $entity
 * @param array $types
 *
 * @return
 */
function commerce_rules_get_custom_fields($entity, $types = array('Integer' => 'integer', 'String' => 'text', 'Date' => 'date')) {
  if (!civicrm_initialize()) {
    return array();
  }
  $fields = civicrm_api3($entity, 'getfields', array('action' => 'create', 'getoptions' => TRUE));
  $fields = $fields['values'];
  foreach ($fields as $field_name => $field) {
    if (substr($field_name, 0, 7) != 'custom_'  || !in_array($field['data_type'], array_keys($types))) {
      unset($fields[$field_name]);
    }
    else {
      $fields[$field_name]['type'] = $types[$field['data_type']];
    }
  }
  return $fields;
}
