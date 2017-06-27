<?php

namespace Drupal\uikit_admin;

use Drupal\Core\Template\Attribute;

/**
 * Provides helper functions for the UIkit Admin theme.
 */
class UIkitAdmin {

  public static function getPageTemplateAttributes() {
    $page_attributes = [];

    // Set the header wrapper attributes.
    $header_wrapper_attributes = new Attribute;
    $header_wrapper_attributes->setAttribute('id', 'page--header-wrapper');
    $header_wrapper_attributes->addClass('uk-block');
    $header_wrapper_attributes->addClass('uk-block-muted');
    $page_attributes['header_wrapper_attributes'] = $header_wrapper_attributes;

    // Set the header attributes.
    $header_attributes = new Attribute;
    $header_attributes->setAttribute('id', 'page--header');
    $header_attributes->addClass('uk-width-9-10');
    $header_attributes->addClass('uk-container-center');
    $header_attributes->addClass('uk-margin');

    // Add top margin to the header attributes if the toolbar module is not
    // installed.
    if (!\Drupal::service('module_handler')->moduleExists('toolbar')) {
      $header_attributes->addClass('uk-margin-top');
    }
    $page_attributes['header_attributes'] = $header_attributes;

    // Set the pre-content attributes.
    $pre_content_attributes = new Attribute;
    $pre_content_attributes->setAttribute('id', 'page--pre-content');
    $pre_content_attributes->addClass('uk-width-1-1');
    $pre_content_attributes->addClass('uk-margin-top');
    $page_attributes['pre_content_attributes'] = $pre_content_attributes;

    // Set the beadcrumb attributes.
    $breadcrumb_attributes = new Attribute;
    $breadcrumb_attributes->setAttribute('id', 'page--breadcrumb');
    $breadcrumb_attributes->addClass('uk-width-1-1');
    $page_attributes['breadcrumb_attributes'] = $breadcrumb_attributes;

    // Set the highlighted attributes.
    $highlighted_attributes = new Attribute;
    $highlighted_attributes->setAttribute('id', 'page--highlighted');
    $highlighted_attributes->addClass('uk-width-9-10');
    $highlighted_attributes->addClass('uk-container-center');
    $highlighted_attributes->addClass('uk-margin');
    $page_attributes['highlighted_attributes'] = $highlighted_attributes;

    // Set the help attributes.
    $help_attributes = new Attribute;
    $help_attributes->setAttribute('id', 'page--help');
    $help_attributes->addClass('uk-width-9-10');
    $help_attributes->addClass('uk-container-center');
    $help_attributes->addClass('uk-margin');
    $page_attributes['help_attributes'] = $help_attributes;

    // Set the content wrapper attributes.
    $content_wrapper_attributes = new Attribute;
    $content_wrapper_attributes->setAttribute('id', 'page--content-wrapper');
    $page_attributes['content_wrapper_attributes'] = $content_wrapper_attributes;

    // Set the content grid attributes.
    $content_grid_attributes = new Attribute;
    $content_grid_attributes->setAttribute('id', 'page--content-grid');
    $content_grid_attributes->addClass('uk-grid');
    $content_grid_attributes->setAttribute('data-uk-grid-margin', '');
    $page_attributes['content_grid_attributes'] = $content_grid_attributes;

    // Set the content attributes.
    $content_attributes = new Attribute;
    $content_attributes->setAttribute('id', 'page--content');
    $content_attributes->addClass('uk-width-9-10');
    $content_attributes->addClass('uk-container-center');
    $content_attributes->addClass('uk-margin');
    $page_attributes['content_attributes'] = $content_attributes;

    return $page_attributes;
  }
}
