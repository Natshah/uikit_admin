<?php

/**
 * @file
 * Set up variables to be placed within the template (.tpl.php) files.
 *
 * @see preprocess.inc
 */

/**
 * Processes a machine-readable name form element.
 *
 * @param array $element
 *   The form element to process. Properties used:
 *   - #machine_name: An associative array containing:
 *     - exists: A function name to invoke for checking whether a submitted
 *       machine name value already exists. The submitted value is passed as
 *       argument. In most cases, an existing API or menu argument loader
 *       function can be re-used. The callback is only invoked, if the submitted
 *       value differs from the element's #default_value.
 *     - source: (optional) The #array_parents of the form element containing
 *       the human-readable name (i.e., as contained in the $form structure) to
 *       use as source for the machine name. Defaults to array('name').
 *     - label: (optional) A text to display as label for the machine name value
 *       after the human-readable name form element. Defaults to "Machine name".
 *     - replace_pattern: (optional) A regular expression (without delimiters)
 *       matching disallowed characters in the machine name. Defaults to
 *       '[^a-z0-9_]+'.
 *     - replace: (optional) A character to replace disallowed characters in the
 *       machine name via JavaScript. Defaults to '_' (underscore). When using a
 *       different character, 'replace_pattern' needs to be set accordingly.
 *     - error: (optional) A custom form error message string to show, if the
 *       machine name contains disallowed characters.
 *     - standalone: (optional) Whether the live preview should stay in its own
 *       form element rather than in the suffix of the source element. Defaults
 *       to FALSE.
 *   - #maxlength: (optional) Should be set to the maximum allowed length of the
 *     machine name. Defaults to 64.
 *   - #disabled: (optional) Should be set to TRUE in case an existing machine
 *     name must not be changed after initial creation.
 */
function uikit_admin_process_machine_name($element, &$form_state) {
  // Apply default form element properties.
  $element += array(
    '#title' => t('Machine-readable name'),
    '#description' => t('A unique machine-readable name. Can only contain lowercase letters, numbers, and underscores.'),
    '#machine_name' => array(),
    '#field_prefix' => '',
    '#field_suffix' => '',
    '#suffix' => '',
  );
  // A form element that only wants to set one #machine_name property (usually
  // 'source' only) would leave all other properties undefined, if the defaults
  // were defined in hook_element_info(). Therefore, we apply the defaults here.
  $element['#machine_name'] += array(
    'source' => array('name'),
    'target' => '#' . $element['#id'],
    'label' => t('Machine name'),
    'replace_pattern' => '[^a-z0-9_]+',
    'replace' => '_',
    'standalone' => FALSE,
    'field_prefix' => $element['#field_prefix'],
    'field_suffix' => $element['#field_suffix'],
  );

  // By default, machine names are restricted to Latin alphanumeric characters.
  // So, default to LTR directionality.
  if (!isset($element['#attributes'])) {
    $element['#attributes'] = array();
  }
  $element['#attributes'] += array('dir' => 'ltr');

  // The source element defaults to array('name'), but may have been overidden.
  if (empty($element['#machine_name']['source'])) {
    return $element;
  }

  // Retrieve the form element containing the human-readable name from the
  // complete form in $form_state. By reference, because we may need to append
  // a #field_suffix that will hold the live preview.
  $key_exists = NULL;
  $source = drupal_array_get_nested_value($form_state['complete form'], $element['#machine_name']['source'], $key_exists);
  if (!$key_exists) {
    return $element;
  }

  $suffix_id = $source['#id'] . '-machine-name-suffix';
  $element['#machine_name']['suffix'] = '#' . $suffix_id;

  if ($element['#machine_name']['standalone']) {
    $element['#suffix'] .= ' <small id="' . $suffix_id . '">&nbsp;</small>';
  }
  else {
    // Append a field suffix to the source form element, which will contain
    // the live preview of the machine name.
    $source += array('#field_suffix' => '<div class="uk-display-inline-block uk-margin-left">');
    $source['#field_suffix'] .= '<small id="' . $suffix_id . '">&nbsp;</small>';
    $source['#field_suffix'] .= '</div>';

    $parents = array_merge($element['#machine_name']['source'], array('#field_suffix'));
    drupal_array_set_nested_value($form_state['complete form'], $parents, $source['#field_suffix']);
  }

  $js_settings = array(
    'type' => 'setting',
    'data' => array(
      'machineName' => array(
        '#' . $source['#id'] => $element['#machine_name'],
      ),
    ),
  );
  $element['#attached']['js'][] = 'misc/machine-name.js';
  $element['#attached']['js'][] = $js_settings;

  return $element;
}
