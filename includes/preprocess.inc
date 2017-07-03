<?php

/**
 * @file
 * Set up variables to be placed within the template (.tpl.php) files.
 *
 * @see process.inc
 */

use Drupal\Core\Template\Attribute;
use Drupal\uikit_admin\UIkitAdmin;

/**
 * Implements template_preprocess_page().
 */
function uikit_admin_preprocess_page(&$variables) {
  // Set page.html.twig template attributes.
  $page_attributes = UIkitAdmin::getPageTemplateAttributes();
  $variables['header_wrapper_attributes'] = $page_attributes['header_wrapper_attributes'];
  $variables['header_attributes'] = $page_attributes['header_attributes'];
  $variables['pre_content_attributes'] = $page_attributes['pre_content_attributes'];
  $variables['breadcrumb_attributes'] = $page_attributes['breadcrumb_attributes'];
  $variables['highlighted_attributes'] = $page_attributes['highlighted_attributes'];
  $variables['help_attributes'] = $page_attributes['help_attributes'];
  $variables['content_wrapper_attributes'] = $page_attributes['content_wrapper_attributes'];
  $variables['content_grid_attributes'] = $page_attributes['content_grid_attributes'];
  $variables['content_attributes'] = $page_attributes['content_attributes'];
}

/**
 * Implements template_preprocess_block().
 */
function uikit_admin_preprocess_block(&$variables) {
  $plugin_id = $variables['plugin_id'];

  switch ($plugin_id) {
    // Set various values based on the plugin id of the block.
    case 'help_block':
      $variables['attributes']['class'][] = 'uk-panel';
      $variables['attributes']['class'][] = 'uk-panel-box';
      break;

    case 'system_messages_block':
      break;
  }
}

/**
 * Implements template_preprocess_details().
 */
function uikit_admin_preprocess_details(&$variables) {
  // Set the accordion attributes.
  $attributes = $variables['attributes'];
  $accordion_attributes = new Attribute;

  foreach ($attributes as $attribute => $value) {
    if ($attribute != 'class' && $attribute != 'open') {
      $accordion_attributes->setAttribute($attribute, $value);
    }
  }
  $accordion_attributes->addClass('uk-form-row');
  $accordion_attributes->addClass('uk-accordion');

  // Set the data-uk-accordion attribute based on the #open value.
  $open = isset($variables['element']['#open']) ? $variables['element']['#open'] : FALSE;
  if ($open) {
    $accordion_attributes->setAttribute('data-uk-accordion', '{showfirst: true}');
  }
  else {
    $accordion_attributes->setAttribute('data-uk-accordion', '{showfirst: false}');
  }

  $variables['accordion_attributes'] = $accordion_attributes;

  // Set the accordion title attributes.
  $accordion_title_attributes = new Attribute;
  $accordion_title_attributes->addClass('uk-accordion-title');
  $variables['accordion_title_attributes'] = $accordion_title_attributes;

  // Set the accordion content attributes.
  $accordion_content_attributes = new Attribute;
  $accordion_content_attributes->addClass('uk-accordion-content');
  $variables['accordion_content_attributes'] = $accordion_content_attributes;

  // Set the error classes.
  $error_classes = new Attribute;
  $error_classes->addClass('uk-alert');
  $error_classes->addClass('uk-alert-danger');
  $variables['error_classes'] = $error_classes;

  // Set the description attributes.
  $description_attributes = new Attribute;
  $description_attributes->addClass('uk-form-help-block');
  $description_attributes->addClass('uk-margin-small-bottom');
  $variables['description_attributes'] = $description_attributes;
}

/**
 * Implements hook_form_alter().
 */
function uikit_admin_preprocess_form(&$variables) {
  $form_id = $variables['element']['#form_id'];
  $orientation = 'stacked';

  // Set the orientation of the form based on the form id.
  switch ($form_id) {
    case 'views_exposed_form':
      $orientation = 'horizontal';
      break;
  }

  // Set the orientation variable.
  $variables['orientation'] = $orientation;
}

/**
 * Implements template_preprocess_input().
 */
function uikit_admin_preprocess_input(&$variables) {
  $type = $variables['element']['#type'];

  if ($type == 'submit') {
    // Set the value variable so we can change submit buttons from an <input>
    // to a <button> element.
    if (is_object($variables['element']['#value'])) {
      $value = $variables['element']['#value']->getUntranslatedString();
    }
    else {
      $value = $variables['element']['#value'];
    }
    $variables['value'] = t('@value', ['@value' => $value]);

    // Add the uk-button class to all buttons.
    $variables['attributes']['class'][] = 'uk-button';

    switch ($value) {
      // Add uk-button-* modifier class based on the value of the button.
      case 'Filter':
      case 'Save blocks':
      case 'Save configuration':
      case 'Update':
        $variables['attributes']['class'][] = 'uk-button-primary';
        break;
    }
  }
}

/**
 * Implements template_preprocess_links() for dropbutton links.
 */
function uikit_admin_preprocess_links__dropbutton(&$variables) {
  // Add the uk-button-primary class based on the type of dropbutton is set.
  if (isset($variables['dropbutton'])) {
    if ($variables['dropbutton']['link']) {
      $variables['dropbutton']['link']['#options']['attributes']['class'][] = 'uk-button-primary';
    }
    elseif ($variables['dropbutton']['text_attributes']) {
      $variables['dropbutton']['text_attributes']['class'][] = 'uk-button-primary';
    }
  }
}

/**
 * Implements template_preprocess_menu_local_tasks().
 */
function uikit_admin_preprocess_menu_local_tasks(&$variables) {
  // Set primary tasks attributes.
  $primary_attributes = new Attribute;
  $primary_attributes->setAttribute('id', 'tasks--primary');
  $primary_attributes->addClass('uk-tab');
  $variables['primary_attributes'] = $primary_attributes;

  // Set secondary tasks attributes.
  $secondary_attributes = new Attribute;
  $secondary_attributes->setAttribute('id', 'tasks--secondary');
  $secondary_attributes->addClass('uk-subnav');
  $secondary_attributes->addClass('uk-subnav-line');
  $secondary_attributes->addClass('uk-margin-bottom-remove');
  $variables['secondary_attributes'] = $secondary_attributes;
}

/**
 * Implements template_preprocess_region().
 */
function uikit_admin_preprocess_region(&$variabes) {
  $region = $variabes['region'];
  $attributes = $variabes['attributes'];

  switch ($region) {
    case 'pre_content':
    case 'breadcrumb':
      $region_attributes = new Attribute;
      $region_attributes->setAttribute('id', $attributes['id']);
      $variabes['attributes'] = $region_attributes;
      break;
  }
}
